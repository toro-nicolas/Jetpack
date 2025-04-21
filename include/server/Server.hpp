/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Server.hpp
*/
/**
 * @file Server.hpp
 * @brief The Server.hpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#ifndef SERVER_HPP_
	#define SERVER_HPP_

    #include "utils/Jetpack.hpp"

namespace Jetpack {
    #define GRAVITY 9.81
    #define JETPACK_SPEED 10.0
	#define PLAYER_SPEED 5.0

	class Server {
		public:
			Server(int ac, char **av);
			~Server();

			Server(const Server &) = delete;
			Server &operator=(const Server &) = delete;
			void run();

            static void sendResponse(int client_fd, CmdID cmd_id, int cmd_code, const std::string &message);

			class Client;

		private:
            /* Initialization functions */
			void _checkArgs(int ac, char **av);
            void _initMap();
			void _initCommands();
			void _initServer();



            /* Command functions */
        protected:

            void executeId(int client_fd, std::vector<std::string> &command);
            void executeMap(int client_fd, std::vector<std::string> &command);
            void executePseudo(int client_fd, std::vector<std::string> &command);
            void executeMove(int client_fd, std::vector<std::string> &command);
            void executeClientsNb(int client_fd, std::vector<std::string> &command);
            void executeClientsStats(int client_fd, std::vector<std::string> &command);
            void executeClientsPositions(int client_fd, std::vector<std::string> &command);



            /* Server functions */
        private:
            void _updatePlayers();
			void _addNewClient();
			void _disconnectClient(std::size_t poll_index);
			void _executeCommand(std::size_t poll_index, const std::string &command);
			void _writeClientAction(std::size_t poll_index);
			void _readClientAction(std::size_t poll_index);
			void _analysePoll(std::size_t poll_index);

            #define MAX_HEIGHT (_map.size() - 1)
            #define MIN_HEIGHT 0

			std::string _port;
			std::string _map_path;
            std::vector<std::string> _map;
			struct sockaddr_in _server;
			std::unique_ptr<Socket> _server_socket;
			std::vector<pollfd> _poll_list;
            std::map<std::size_t, std::unique_ptr<Client>> _clients; /* fd, client */
            std::chrono::time_point<std::chrono::high_resolution_clock> _last_update;
            double _map_x_pos = 0;



			std::unordered_map<std::string, std::function<void(int client_fd, std::vector<std::string> &command)>> _commands;
	};
}

#endif /* SERVER_HPP_ */
