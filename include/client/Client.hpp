/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Client.hpp
*/
/**
 * @file Client.hpp
 * @brief The Client.hpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#ifndef CLIENT_HPP_
	#define CLIENT_HPP_

	#include "client/Player.hpp"
    #include "client/Coin.hpp"
    #include "client/Trap.hpp"
    #include "utils/PositionHash.hpp"

namespace Jetpack {
    /**
     * @class Client
     * @brief A class that represents the client
     */
	class Client
	{
		public:
			/* Constructor and destructor */

			/**
             * @brief Constructor for Client class
             * @param ac Number of command line arguments
			 * @param av Array of command line arguments
             */
			Client(int ac, char **av);
			/**
			 * @brief Destructor for Client class
			 */
			~Client();
			/**
			 * @brief Deleted copy constructor
			 * @param other The other Client object to copy from
			 */
			Client(const Client &) = delete;
			/**
			 * @brief Deleted assignment operator
			 * @param other The other Client object to assign from
			 * @return Reference to the current object
			 */
			Client &operator=(const Client &) = delete;



			/* Protocol functions */

            typedef std::tuple<CmdID, int, std::string> response_t; /* A tuple containing the command ID, the code and the message */

			/**
			 * @brief Sends a command to the server
			 * @param fd The file descriptor of the socket
			 * @param command The command to send
			 */
            void sendCommand(int fd, const std::vector<std::string> &command);
            /**
             * @brief Receives a response from the server
             * @return A pair containing the code and the message
             */
            std::pair<int, std::string> getResponse();
			/**
			 * @brief Receives a response from the server
			 * @return A tuple containing the command ID, the code and the message
			 */
            response_t getJetpackResponse();



			/* Client functions */

            static std::mutex isRunningMutex; /* Mutex for isRunning */
            static bool isRunning; /* The running status of the client (used to stop the client) */

            /**
             * @brief Closes the client
             * @note This function is a signal handler for SIGINT
             * @param signal The signal to close the client
             */
            static void closeJetpackClient(int signal);
			/**
			 * @brief Runs the client
			 * @note This function is the main loop of the client
			 */
			void run();




		private:
			/* The state of the music */
            enum class MusicState {
                NONE,
				PLAYING,
                PAUSED,
                STOPPED,
            };



			/* Initialization functions */

            /**
             * @brief Check the arguments passed to the client
             * @param ac The number of arguments
             * @param av The arguments
             * @throw JetpackError If the arguments are invalid
             * @throw JetpackUsage If the help flag is passed
             */
			void _checkArgs(int ac, char **av);
			/**
			 * @brief Initializes the commands of the client
			 */
			void _initCommands();
			/**
			 * @brief Initializes the game information
             * @throw JetpackError If the ID or MAP command fails
			 */
			void _initGameInformation();
			/**
			 * @brief Initializes the client
             * @throw JetpackError If the connection fails
			 */
			void _initClient();
			/**
             * @brief Initializes the FX for the game
             * @throw JetpackError If the FX initialization fails
			 */
			void _initFx();
			/**
             * @brief Initializes the music for the game
             * @throw JetpackError If the music initialization fails
			 */
            void _initMusic();
			/**
             * @brief Initializes the elements of the game
             * @throw JetpackError If the elements initialization fails
			 */
			void _initElements();
			/**
             * @brief Initializes the SFML window and all game elements
             * @throw JetpackError If the SFML initialization fails
			 */
            void _initSfml();



            /* Thread functions */

			/**
			 * @brief Thread for handling user input
			 */
            void _promptThread();
			/**
			 * @brief Thread for handling communication with the server
			 */
            void _communicationThread();
			/**
			 * @brief Thread for handling the game loop
			 */
            void _gameThread();



            /* Game functions */

			/**
			 * @brief Updates the game from the server responses
			 */
            void _updateFromResponse();
			/**
			 * @brief Updates the animation
			 * @param deltaTime The time since the last update
			 */
			void _updateAnimation(float deltaTime);
            /**
             * @brief Updates the menu
             * @param deltaTime The time since the last update
             */
            void _updateMenu(float deltaTime);
            /**
             * @brief Updates the game
             * @param deltaTime The time since the last update
             */
            void _updateGame(float deltaTime);
			/**
			 * @brief Updates the client
			 * @param deltaTime The time since the last update
			 */
            void _update(float deltaTime);
            /**
             * @brief Draws the elements of the menu
             */
            void _drawMenu();
            /**
             * @brief Draws the elements of the game
             */
            void _drawGame();
            /**
             * @brief Draws the elements of the end
             */
            void _drawEnd();
			/**
			 * @brief Draws the elements on the screen depending on the game state
			 */
            void _draw();
			/**
             * @brief Analyses the events of the game
			 */
			void _analyseEvent();



        protected:
			/* Command functions */

            std::unordered_map<std::string, std::function<void(std::vector<std::string> &command)>> _commands; /* The map of commands (command name, function) */

			/**
			 * @brief Executes the exit command
			 * @param command The command to execute
			 */
            void executeExit(std::vector<std::string> &command);



			/* Response handler functions */

			/**
			 * @brief Handles the response of the command ID
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandId(const int &code, const std::string &message);
			/**
			 * @brief Handles the response of the command MAP
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandMap(const int &code, const std::string &message);
			/**
			 * @brief Handles the response of the command PSEUDO
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandPseudo(const int &code, const std::string &message);
			/**
			 * @brief Handles the response of the command MOVE
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandMove(const int &code, const std::string &message);
			/**
			 * @brief Handles the response of the command CLIENT_NB
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandClientsNb(const int &code, const std::string &message);
			/**
			 * @brief Handles the response of the command CLIENTS_STATS
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandClientsStats(const int &code, const std::string &message);
			/**
			 * @brief Handles the response of the command CLIENTS_POSITIONS
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandClientsPositions(const int &code, const std::string &message);



        private:
			/* Client information */

			std::string _ip; /* The IP address of the server */
			std::string _port; /* The port of the server */
			std::unique_ptr<Socket> _client_socket; /* The socket of the client */
			struct sockaddr_in _client; /* The address of the client */
            std::mutex _commands_queue_mutex; /* Mutex for the commands queue */
            std::queue<std::vector<std::string>> _commands_queue; /* The queue of commands to send to the server */
            std::mutex _response_queue_mutex; /* Mutex for the response queue */
            std::queue<response_t> _response_queue; /* The queue of responses from the server */



			/* Game information */

            enum GameState {
                MAIN_MENU,
                GAME,
                END
            };

            GameState _gameState = MAIN_MENU; /* The game state */
			std::size_t _id; /* The ID of the client */
			std::vector<std::string> _map; /* The map of the game */
			std::size_t _nb_players = 0; /* The number of players */
            std::map<size_t, std::unique_ptr<Player>> _players; /* The map of players (ID, Player) */
            std::string _winner; /* The winner of the game */



			/* Graphical elements */

			static constexpr float WINDOW_WIDTH = 1280.0f; /* The width of the window */
			static constexpr float WINDOW_HEIGHT = 720.0f; /* The height of the window */
			sf::RenderWindow _window; /* The window of the game */
			#define NB_LINES _map.size() /* The number of lines in the map */
			#define RATIO (WINDOW_HEIGHT / static_cast<float>(NB_LINES)) /* The size of a tile */


				/* Text */

				sf::Font _font; /* The font of the text */
				sf::Text _text; /* The text to display */


				/* Music */

				sf::Music _menuMusic; /* The menu music */
				MusicState _menuMusicState = MusicState::NONE; /* The state of the menu music */

				sf::Music _gameMusic; /* The game music */
				MusicState _gameMusicState = MusicState::NONE; /* The state of the game music */


				/* Fx */

				sf::SoundBuffer _jetpackSoundStartBuffer; /* The jetpack sound start buffer */
				sf::Sound _jetpackSoundStart; /* The jetpack sound start */

				sf::SoundBuffer _jetpackSoundStopBuffer; /* The jetpack sound stop buffer */
				sf::Sound _jetpackSoundStop; /* The jetpack sound stop */

				sf::SoundBuffer _jetpackSoundDownBuffer; /* The jetpack sound down buffer */
				sf::Sound _jetpackSoundDown; /* The jetpack sound down */

				sf::SoundBuffer _jetpackSoundUpBuffer; /* The jetpack sound up buffer */
				sf::Sound _jetpackSoundUp; /* The jetpack sound up */

				sf::SoundBuffer _coinSoundBuffer; /* The coin sound buffer */
				sf::Sound _coinSound; /* The coin sound */

				sf::SoundBuffer _zappedSoundBuffer; /* The zapped sound buffer */
				sf::Sound _zappedSound; /* The zapped sound */

				sf::SoundBuffer _firedSoundBuffer; /* The fired sound buffer */
				sf::Sound _firedSound; /* The fired sound */


				/* Background */

				sf::Texture _background_texture; /* The background texture */
				sf::Sprite _background_sprite; /* The background sprite */
				float _background_size; /* The size of the background */
				float _background_pos = 0.f; /* The position of the background */
				static constexpr float BACKGROUND_SPEED = 100.0f; /* The speed of the background */


				/* Player */

				sf::Texture _player_texture; /* The player texture */
				sf::Sprite _player_sprite; /* The player sprite */
				bool _jetpack = false; /* The jetpack status */
				Player::PlayerState _curent_state = Player::PlayerState::NORMAL; /* The current state of the player */


				/* Coin */

				sf::Texture _coin_texture; /* The coin texture */
				sf::Sprite _coin_sprite; /* The coin sprite */
				Animation _coin_animation; /* The coin animation */
                std::unordered_map<std::array<std::size_t, 2>, std::unique_ptr<Coin>, PositionHash> _coins; /* The map of coins (position, Coin) */


                /* Traps */
                std::unordered_map<std::array<std::size_t, 2>, std::unique_ptr<Trap>, PositionHash> _traps; /* The map of traps (position, Trap) */

                    /* Zapper */
                    sf::Texture _zapper_texture; /* The zapper texture */
                    sf::Sprite _zapper_sprite; /* The zapper sprite */
                    Animation _zapper_animation; /* The zapper animation */

                    /* Lazer */
                    sf::Texture _laser_texture; /* The laser texture */
                    sf::Sprite _laser_sprite; /* The laser sprite */
                    Animation _laser_animation; /* The laser animation */

                    /* Missile */
                    sf::Texture _missile_texture; /* The missile texture */
                    sf::Sprite _missile_sprite; /* The missile sprite */
                    Animation _missile_animation; /* The missile animation */
	};
}

#endif /* CLIENT_HPP_ */
