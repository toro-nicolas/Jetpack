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

    constexpr int START_FD = 4;
    constexpr double GRAVITY = 9.81;
    constexpr double JETPACK_SPEED = 10.0;
    constexpr double PLAYER_SPEED = 5.0;
    constexpr char INVALID_PSEUDO_CHARACTERS[] = ":| \t\n\r";

    /**
     * @class Server
     * @brief A class that represents the server
     */
	class Server {
		public:
            /* Constructor and destructor */

            /**
             * @brief Constructor for Server class
             * @param ac Number of command line arguments
             * @param av Array of command line arguments
             * @throw JetpackError If the arguments are invalid
             */
			Server(int ac, char **av);
            /**
             * @brief Destructor for Server class
             */
			~Server();
            /**
             * @brief Deleted copy constructor
             * @param other The other Server object to copy from
             */
			Server(const Server &) = delete;
            /**
             * @brief Deleted assignment operator
             * @param other The other Server object to assign from
             * @return Reference to the current object
             */
			Server &operator=(const Server &) = delete;



            /* Protocol functions */

            /**
             * @brief Sends a response to the client
             * @param client_fd The file descriptor of the client
             * @param cmd_id The command ID
             * @param cmd_code The command code
             * @param message The message to send
             */
            static void sendResponse(int client_fd, CmdID cmd_id, int cmd_code, const std::string &message);



            /* Server functions */

            /**
             * @brief Runs the server
             * @note This function is the main loop of the server
             * @throw JetpackError If the poll fails
             */
			void run();



			class Client; /* Forward declaration of Client class */



		private:
            /* Initialization functions */

            /**
             * @brief Checks the command line arguments
             * @param ac Number of command line arguments
             * @param av Array of command line arguments
             * @throw JetpackError If the arguments are invalid
             * @throw JetpackUsage If the help flag is passed
             */
			void _checkArgs(int ac, char **av);
            /**
             * @brief Initializes the map of the game
             * @throw JetpackError If the map file is empty or cannot be opened
             */
            void _initMap();
            /**
             * @brief Initializes the commands of the server
             */
			void _initCommands();
            /**
             * @brief Initializes the server
             * @throw JetpackError If the server cannot be initialized
             */
			void _initServer();



            /* Server game functions */

            /**
             * @brief Checks if the player is on the map
             * @param x The x position of the player
             * @param y The y position of the player
             * @param c The character to check
             * @return True if the player is on the map, false otherwise
             */
            bool _isPlayerOn(const double &x, const double &y, const char c) const;
            /**
             * @brief Analyse if the client is on a coin
             * and add it to the client coin list
             * @param client The client to analyse
             */
            void _analyseClientOnCoin(Client &client);
            /**
             * @brief Updates a client (player)
             * @param client The client to update
             * @param delta_time The time since the last frame
             * @param reset_coins True if the coins should be reset
             * and false if not
             */
            void _updatePlayer(Client &client, double &delta_time, bool &reset_coins);
            /**
             * @brief Updates the game
             * @note This function is called every frame/poll
             */
            void _updateGame();



            /* Server sub-functions */

            /**
             * @brief Adds a new client to the server
             * @throw JetpackError If the accept fails
             */
            void _addNewClient();
            /**
             * @brief Disconnects a client from the server
             * @param poll_index The index of the client in the poll list
             */
            void _disconnectClient(std::size_t poll_index);
            /**
             * @brief Executes a command
             * @param poll_index The index of the client in the poll list
             * @param command The command to execute
             */
            void _executeCommand(std::size_t poll_index, const std::string &command);
            /**
             * @brief Writes a response to the client
             * @param poll_index The index of the client in the poll list
             */
            void _writeClientAction(std::size_t poll_index);
            /**
             * @brief Reads a command from the client
             * @param poll_index The index of the client in the poll list
             * @throw JetpackError If the read fails
             */
            void _readClientAction(std::size_t poll_index);
            /**
             * @brief Analyzes the poll events
             * @param poll_index The index of the client in the poll list
             */
            void _analysePoll(std::size_t poll_index);



        protected:
            /* Command functions */

            std::unordered_map<std::string, std::function<void(int client_fd, std::vector<std::string> &command)>> _commands; /* The map of commands (command name, function) */

            /**
             * @brief Executes the ID command
             * @param client_fd The file descriptor of the client
             * @param command The command to execute
             */
            void executeId(int client_fd, std::vector<std::string> &command);
            /**
             * @brief Executes the MAP command
             * @param client_fd The file descriptor of the client
             * @param command The command to execute
             */
            void executeMap(int client_fd, std::vector<std::string> &command);
            /**
             * @brief Executes the PSEUDO command
             * @param client_fd The file descriptor of the client
             * @param command The command to execute
             */
            void executePseudo(int client_fd, std::vector<std::string> &command);
            /**
             * @brief Executes the MOVE command
             * @param client_fd The file descriptor of the client
             * @param command The command to execute
             */
            void executeMove(int client_fd, std::vector<std::string> &command);
            /**
             * @brief Executes the CLIENTS_NB command
             * @param client_fd The file descriptor of the client
             * @param command The command to execute
             */
            void executeClientsNb(int client_fd, std::vector<std::string> &command);
            /**
             * @brief Executes the CLIENTS_STATS command
             * @param client_fd The file descriptor of the client
             * @param command The command to execute
             */
            void executeClientsStats(int client_fd, std::vector<std::string> &command);
            /**
             * @brief Executes the CLIENTS_POSITIONS command
             * @param client_fd The file descriptor of the client
             * @param command The command to execute
             */
            void executeClientsPositions(int client_fd, std::vector<std::string> &command);



        private:
            #define MAX_HEIGHT (_map.size() - 1)
            #define MIN_HEIGHT 0

			std::string _port; /* The port of the server */
			std::string _map_path; /* The path of the map */
            bool _infinite_mode = false; /* The infinite mode of the game */
            std::vector<std::string> _map; /* The map of the game */
			struct sockaddr_in _server; /* The address of the server */
			std::unique_ptr<Socket> _server_socket; /* The socket of the server */
			std::vector<pollfd> _poll_list; /* The list of clients */
            std::map<std::size_t, std::unique_ptr<Client>> _clients; /* The map of clients (client fd, client object) */
            std::chrono::time_point<std::chrono::high_resolution_clock> _last_update; /* The last update time */
            double _map_x_pos = 0; /* The x position of the map */
	};
}

#endif /* SERVER_HPP_ */
