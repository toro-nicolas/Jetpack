/*
** EPITECH PROJECT, 2025
** client
** File description:
** The Client.cpp
*/
/**
 * @file Client.cpp
 * @brief The Client.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
    bool Client::isRunning = false;
    std::mutex Client::isRunningMutex;

    void Client::closeJetpackClient(UNUSED int signal)
    {
        DEBUG << "Close client";
        std::lock_guard<std::mutex> lock(isRunningMutex);
        isRunning = false;
    }

	void Client::_checkArgs(int ac, char **av)
	{
		DEBUG << "CheckArgs AC: " << ac;
		for (int index = 1; index < ac; index++) {
            if (std::string(av[index]) == "-d") {
                Logs::debug_mode = true;
                continue;
            }
            if (std::string(av[index]) == "--help") {
                throw JetpackUsage();
            }
            if (std::string(av[index]) == "-h" && index + 1 < ac) {
                index++;
                _ip = std::string(av[index]);
                continue;
            }
            if (std::string(av[index]) == "-p" && index + 1 < ac) {
                index++;
                _port = std::string(av[index]);
                continue;
            }
            throw JetpackError("Invalid or incomplete argument: " + std::string(av[index]));
        }

		if (!std::all_of(_ip.begin(), _ip.end(), [](char c) { return ::isdigit(c) || c == '.'; }))
			throw JetpackError("Invalid server IP address: " + _ip);
		if (!std::all_of(_port.begin(), _port.end(), ::isdigit)
		|| _port.size() > 5 || _port.empty())
			throw JetpackError("Invalid port number: " + _port);
	}

    void Client::sendCommand(int fd, const std::vector<std::string> &command)
    {
        std::string commandStr;

        for (std::size_t index = 0; index < command.size(); index++) {
            if (index != 0)
                commandStr += " ";
            commandStr += command[index];
        }
        DEBUG << "Send command: " << commandStr;
        commandStr += ENDL;
        if (dprintf(fd, "%s", commandStr.c_str()) < 0) {
            ERROR << "Server closed the connection.";
            closeJetpackClient(0);
        }
    }

    std::pair<int, std::string> Client::getResponse()
    {
        char tmp = 0;
        std::string response;
        std::size_t index = 0;
        bool findEnd = false;
        int code = 0;
        std::string message;
        int read_size = 0;

        read_size = read(_client_socket->getSocket(), &tmp, 1) >= 0;
        while (read_size > 0) {
            response += tmp;
            if (tmp == '\n')
                break;
            read_size = read(_client_socket->getSocket(), &tmp, 1);
        }
        if (read_size == -1) {
            ERROR << "Server closed the connection.";
            closeJetpackClient(0);
        }
        if (response.size() >= 4 && response[3] == '-') {
            while (read(_client_socket->getSocket(), &tmp, 1)) {
                response += tmp;
                if (index == 3 && tmp == ' ' && response.substr(response.size() -4, 3) == response.substr(0, 3))
                    findEnd = true;
                if (tmp == '\n' && findEnd)
                    break;
                index++;
                if (tmp == '\n')
                    index = 0;
            }
        }
        while (!response.empty() && (response.back() == '\n' || response.back() == '\r'))
            response.pop_back();
        DEBUG << response;
        if (response.size() >= 3)
            code = std::stoi(response.substr(0, 3));
        if (response.size() >= 4)
            message = response.substr(4);
        return std::make_pair(code, message);
    }

    Client::response_t Client::getJetpackResponse()
	{
		char tmp = 0;
		std::string response;
		std::size_t index = 0;
		bool findEnd = false;
        CmdID cmd_id = CMD_ID_NOT_FOUND;
        int code = 0;
        std::string message;
        int read_size = 0;

        read_size = read(_client_socket->getSocket(), &tmp, 1);
        while (read_size > 0) {
            response += tmp;
            if (tmp == '\n')
                break;
            read_size = read(_client_socket->getSocket(), &tmp, 1);
        }
        if (read_size == -1) {
            ERROR << "Server closed the connection.";
            closeJetpackClient(0);
        }
		if (response.size() >= 4 && response[3] == '-') {
			while (read(_client_socket->getSocket(), &tmp, 1) >= 0) {
				response += tmp;
				if (index == 3 && tmp == ' ' && response.substr(response.size() -4, 3) == response.substr(0, 3))
					findEnd = true;
				if (tmp == '\n' && findEnd)
					break;
				index++;
				if (tmp == '\n')
					index = 0;
			}
		}
        while (!response.empty() && (response.back() == '\n' || response.back() == '\r'))
            response.pop_back();
		DEBUG << response;
        if (response.size() >= 2 && response[1] == ' ')
            cmd_id = static_cast<CmdID>(std::stoi(response.substr(0, 1)));
        if (response.size() >= 5)
            code = std::stoi(response.substr(2, 3));
        if (response.size() >= 6)
            message = response.substr(6, response.size() - 6);
		return std::make_tuple(cmd_id, code, message);
	}

	void Client::_initGameInformation()
	{
		response_t response;

		sendCommand(_client_socket->getSocket(), {"ID"});
		response = getJetpackResponse();
		if (std::get<0>(response) != CMD_ID_ID || std::get<1>(response) != CODE_OK + CODE_GAME)
			throw JetpackError("ID command failed: " +
            std::to_string(std::get<0>(response)) + " " +
            std::to_string(std::get<1>(response)) + " " + std::get<2>(response));
		handleCommandId(std::get<1>(response), std::get<2>(response));
		sendCommand(_client_socket->getSocket(), {"MAP"});
		response = getJetpackResponse();
        if (std::get<0>(response) != CMD_MAP_ID || std::get<1>(response) != CODE_OK + CODE_GAME)
			throw JetpackError("MAP command failed: " +
            std::to_string(std::get<0>(response)) + " " +
            std::to_string(std::get<1>(response)) + " " + std::get<2>(response));
        handleCommandMap(std::get<1>(response), std::get<2>(response));
	}

	void Client::_initCommands()
	{
		DEBUG << "Init commands";
		_commands["exit"] = [this](std::vector<std::string> &command) { executeExit(command); };
	}

	void Client::_initClient()
	{
		DEBUG << "Init client: IP: " << _ip << " PORT: " << _port;
		_client_socket = std::make_unique<Socket>(AF_INET, SOCK_STREAM, 0);
		_client.sin_family = AF_INET;
		_client.sin_addr.s_addr = inet_addr(_ip.c_str());
		_client.sin_port = htons(std::stoi(_port));
		if (connect(_client_socket->getSocket(), (const struct sockaddr *)&_client, sizeof(_client)) == -1)
			throw JetpackError("Connect failed: " + std::string(strerror(errno)));
		std::cout << DARK_GREY "Connecting to Jetpack server..." RESET << std::endl;
		if (getResponse().first != 220)
			throw JetpackError("Connection failed.");
		std::cout << BOLD "Connected to Jetpack server (" << _ip << ":" << _port << ")." RESET << std::endl;
		_initGameInformation();
		_initCommands();
	}

	Client::Client(int ac, char **av)
	{
		DEBUG << "Client creation";
		_checkArgs(ac, av);
		_initClient();
        _initSfml();
	}

	Client::~Client()
	{
		DEBUG << "Client destruction";
	}

    void Client::_promptThread()
    {
        std::string line;
        std::vector<std::string> command;
        response_t response;

        std::cout << "> ";
        while (isRunning && std::getline(std::cin, line)) {
            command = stringToVector(line, " \t");
            if (command.empty()) {
                std::cout << "> ";
                continue;
            }
            if (_commands.find(command[0]) == _commands.end()) {
                DEBUG << "Command not found. Sending raw command to server :";
                DEBUG << line;
                dprintf(_client_socket->getSocket(), "%s" ENDL, line.c_str());
                response = getJetpackResponse();
                std::cout << LIGHT_GREY "Server response: " << CMD_ID_STR[std::get<0>(response)] << ": " << std::get<1>(response) << ": " << std::get<2>(response) << RESET;
				std::unique_lock<std::mutex> lock_response_queue(_response_queue_mutex);
				_response_queue.push(response);
				lock_response_queue.unlock();
            } else
                _commands[command[0]](command);
            std::cout << "> ";
        }
    }

    void Client::_communicationThread()
    {
        std::pair<int, std::string> response;

        poll(nullptr, 0, 0);
        while (isRunning) {
            std::unique_lock<std::mutex> lock_commands_queue(_commands_queue_mutex);
            if (!_commands_queue.empty()) {
                std::vector<std::string> command = _commands_queue.front();
                _commands_queue.pop();
                sendCommand(_client_socket->getSocket(), command);
                std::unique_lock<std::mutex> lock_response_queue(_response_queue_mutex);
                _response_queue.push(getJetpackResponse());
                lock_response_queue.unlock();
            }
            lock_commands_queue.unlock();
        }
    }

	void Client::run()
	{
        if (write(STDOUT_FILENO, "Client run\n", 12))
			DEBUG << "Client is running";
        isRunning = true;

        #ifdef DEBUG_MODE
        std::thread promptThread(&Client::_promptThread, this);
        #endif
        std::thread communicationThread(&Client::_communicationThread, this);

        _gameThread();
        #ifdef DEBUG_MODE
        promptThread.join();
        #endif
        communicationThread.join();
	}
}