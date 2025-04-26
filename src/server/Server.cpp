/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Server.cpp
*/
/**
 * @file Server.cpp
 * @brief The Server.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "server/ServerClient.hpp"

namespace Jetpack {
    /**
     * @brief Check the arguments passed to the server
     * @param ac The number of arguments
     * @param av The arguments
     * @throw JetpackError If the arguments are invalid
     * @throw JetpackUsage If the help flag is passed
     */
	void Server::_checkArgs(int ac, char **av)
	{
		DEBUG << "CheckArgs AC: " << ac;
        for (int index = 1; index < ac; index++) {
            if (std::string(av[index]) == "-d") {
                Logs::debug_mode = true;
                continue;
            }
            if (std::string(av[index]) == "-i") {
                _infinite_mode = true;
                continue;
            }
            if (std::string(av[index]) == "--help") {
                throw JetpackUsage();
            }
            if (std::string(av[index]) == "-p" && index + 1 < ac) {
                index++;
                _port = std::string(av[index]);
                continue;
            }
            if (std::string(av[index]) == "-m" && index + 1 < ac) {
                index++;
                _map_path = std::string(av[index]);
                continue;
            }
            throw JetpackError("Invalid or incomplete argument: " + std::string(av[index]));
        }

		if (!std::all_of(_port.begin(), _port.end(), ::isdigit)
		|| _port.size() > 5 || _port.empty())
			throw JetpackError("Invalid port number: " + _port);
		if (!std::filesystem::is_regular_file(_map_path))
			throw JetpackError("Invalid map path: " + _map_path);
	}

    /**
     * @brief Initialize the map from the file
     * @throw JetpackError If the map file is empty or cannot be opened
     */
    void Server::_initMap()
    {
        std::ifstream map_file;
        std::string line;

        DEBUG << "Init map";
        map_file.open(_map_path);
        if (!map_file.is_open())
            throw JetpackError("Failed to open map file: " + _map_path);
        while (std::getline(map_file, line)) {
            if (!line.empty())
                _map.push_back(line);
        }
        map_file.close();
        if (_map.empty())
            throw JetpackError("Map file is empty: " + _map_path);
    }

    /**
     * @brief Initialize the commands of the server
     */
	void Server::_initCommands()
	{
		DEBUG << "Init server commands";
        _commands["ID"] = [this](std::size_t id, std::vector<std::string> &args) { executeId(id, args); };
        _commands["MAP"] = [this](std::size_t id, std::vector<std::string> &args) { executeMap(id, args); };
        _commands["PSEUDO"] = [this](std::size_t id, std::vector<std::string> &args) { executePseudo(id, args); };
        _commands["MOVE"] = [this](std::size_t id, std::vector<std::string> &args) { executeMove(id, args); };
        _commands["CLIENTS_NB"] = [this](std::size_t id, std::vector<std::string> &args) { executeClientsNb(id, args); };
        _commands["CLIENTS_STATS"] = [this](std::size_t id, std::vector<std::string> &args) { executeClientsStats(id, args); };
        _commands["CLIENTS_POSITIONS"] = [this](std::size_t id, std::vector<std::string> &args) { executeClientsPositions(id, args); };
    }

    /**
     * @brief Initialize the server
     * @throw JetpackError If the server cannot be initialized
     */
	void Server::_initServer()
	{
		DEBUG << "InitServer: PORT: " << _port;
		memset(&_server, 0, sizeof(_server));
		_server.sin_family = AF_INET;
		_server.sin_addr.s_addr = INADDR_ANY;
		_server.sin_port = htons(std::stoi(_port));
		_server_socket = std::make_unique<Socket>(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (bind(_server_socket->getSocket(), (struct sockaddr *)&_server, sizeof(_server)) < 0)
			throw JetpackError("Bind failed: " + std::string(strerror(errno)));
		if (listen(_server_socket->getSocket(), MAX_CLIENTS) < 0)
			throw JetpackError("Listen failed: " + std::string(strerror(errno)));
		_poll_list.push_back({ _server_socket->getSocket(), POLLIN | POLLOUT, 0 });
		_initCommands();
	}

    /**
     * @brief Constructor for Server class
     * @param ac Number of command line arguments
     * @param av Array of command line arguments
     * @throw JetpackError If the arguments are invalid
     */
	Server::Server(int ac, char **av)
	{
		DEBUG << "Server creation";
		_checkArgs(ac, av);
        _initMap();
		_initServer();
        if (!write(STDOUT_FILENO, "Server started\n", 16))
			DEBUG << "Server is starting";
	}

    /**
     * @brief Destructor for Server class
     */
	Server::~Server()
	{
		DEBUG << "Server destruction";
	}

    /**
     * @brief Adds a new client to the server
     * @throw JetpackError If the accept fails
     */
	void Server::_addNewClient()
	{
		struct sockaddr_in client_addr{};
		socklen_t client_size = sizeof(client_addr);
		int client_socket = accept(_server_socket->getSocket(), (struct sockaddr *)&client_addr, &client_size);

		if (client_socket < 0)
			throw JetpackError("Accept failed: " + std::string(strerror(errno)));
		_poll_list.push_back({client_socket, POLLIN, 0});
		_clients[client_socket] = std::make_unique<Client>(client_socket, client_addr, MAX_HEIGHT);
        sendResponse(client_socket, CMD_ID_NOT_FOUND, 220, "Connected to Jetpack server. ID: " + std::to_string(client_socket));
		DEBUG << "Client connected: \"" << _clients[client_socket]->getPseudo() << "\" " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port);
	}

    /**
     * @brief Disconnects a client from the server
     * @param poll_index The index of the client in the poll list
     */
	void Server::_disconnectClient(std::size_t poll_index)
	{
        _clients.erase(_poll_list[poll_index].fd);
		close(_poll_list[poll_index].fd);
		_poll_list.erase(_poll_list.begin() + poll_index);
	}

    /**
     * @brief Executes a command
     * @param poll_index The index of the client in the poll list
     * @param command The command to execute
     */
	void Server::_executeCommand(std::size_t poll_index, const std::string &command)
	{
		std::vector<std::string> command_vector = stringToVector(command, " \t\n");

		DEBUG << "Execute command: " << command;
		if (!command_vector.empty() && _commands.find(command_vector[0]) != _commands.end())
			_commands[command_vector[0]](_poll_list[poll_index].fd, command_vector);
		else {
			if (!command_vector.empty())
				ERROR << "Unknown command: " << command_vector[0];
            sendResponse(_poll_list[poll_index].fd, CMD_ID_NOT_FOUND, 500, "Unknown command.");
		}
		if (!command_vector.empty() && command_vector[0] == "QUIT")
			_disconnectClient(poll_index);
	}

    /**
     * @brief Writes a response to the client
     * @param poll_index The index of the client in the poll list
     */
	void Server::_writeClientAction(std::size_t poll_index)
	{
		std::string command = _clients[_poll_list[poll_index].fd]->getNextCommand();
		std::size_t separator_pos = command.find("\n");

		DEBUG << "Write client action: " << poll_index;
		if (separator_pos != std::string::npos) {
			_clients[_poll_list[poll_index].fd]->setNextCommand(command.substr(separator_pos + 1));
			command = command.substr(0, separator_pos);
			_executeCommand(poll_index, command);
		} else
			_clients[_poll_list[poll_index].fd]->setNextCommand(command);
		_poll_list[poll_index].events &= ~POLLOUT;
	}

    /**
     * @brief Reads a command from the client
     * @param poll_index The index of the client in the poll list
     * @throw JetpackError If the read fails
     */
	void Server::_readClientAction(std::size_t poll_index)
	{
		std::string command = _clients[_poll_list[poll_index].fd]->getNextCommand();
		std::string buffer;
		std::size_t separator_pos;
		int size = 0;

		DEBUG << "Read client action: " << poll_index;
		if (ioctl(_poll_list[poll_index].fd, FIONREAD, &size) < 0)
			throw JetpackError("Ioctl failed: " + std::string(strerror(errno)));
		if (size == 0)
			return _disconnectClient(poll_index);
		buffer = std::string(size, 0);
		if (read(_poll_list[poll_index].fd, buffer.data(), size) <= 0)
			return _disconnectClient(poll_index);
		_clients[_poll_list[poll_index].fd]->setNextCommand(command + buffer);
		separator_pos = _clients[_poll_list[poll_index].fd]->getNextCommand().find("\n");
		if (separator_pos != std::string::npos) {
			_poll_list[poll_index].events |= POLLOUT;
		}
	}

    /**
     * @brief Analyzes the poll events
     * @param poll_index The index of the client in the poll list
     */
	void Server::_analysePoll(std::size_t poll_index)
	{
		if (_poll_list[poll_index].revents & POLLOUT) {
			_writeClientAction(poll_index);
		}
		if (_poll_list[poll_index].revents & POLLIN) {
			if (_poll_list[poll_index].fd == _server_socket->getSocket()) {
				_addNewClient();
			} else {
				_readClientAction(poll_index);
			}
		}
	}

    /**
     * @brief Runs the server
     * @note This function is the main loop of the server
     * @throw JetpackError If the poll fails
     */
	void Server::run()
	{
		DEBUG << "Server run";
        _last_update = std::chrono::high_resolution_clock::now();
		while (true) {
			if (poll(_poll_list.data(), _poll_list.size(), 0) < 0)
				throw JetpackError("Poll failed: " + std::string(strerror(errno)));
			for (std::size_t index = 0; index < _poll_list.size(); index++) {
				_analysePoll(index);
			}
            _updateGame();
		}
	}

    /**
     * @brief Sends a response to the client
     * @param client_fd The file descriptor of the client
     * @param cmd_id The command ID
     * @param cmd_code The command code
     * @param message The message to send
     */
    void Server::sendResponse(int client_fd, CmdID cmd_id, int cmd_code, const std::string &message)
    {
        if (cmd_id == CMD_ID_NOT_FOUND) {
            dprintf(client_fd, "%d %s\n", cmd_code, message.c_str());
            DEBUG << "Send response: " << " " << cmd_code << " " << message;
        } else {
            dprintf(client_fd, "%d %d %s\n", cmd_id, cmd_code,
                message.c_str());
            DEBUG << "Send response: " << CMD_ID_STR[cmd_id] << " " << cmd_code << " " << message;
        }
    }
}
