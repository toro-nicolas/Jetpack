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
    #include "client/Zapper.hpp"

namespace Jetpack {
	class Client
	{
		public:
			/* Constructor and destructor */

			/**
             * @brief Constructor for Animation class
             * @param ac Number of command line arguments
			 * @param av Array of command line arguments
             */
			Client(int ac, char **av);

			/**
			 * @brief Destructor for Animation class
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

            typedef std::tuple<CmdID, int, std::string> response_t; /* A tuple containing the command ID, the code and the message */

			/**
			 * @brief Receives a response from the server
			 * @return A tuple containing the command ID, the code and the message
			 */
            response_t getJetpackResponse();

			/* Run functions */

			/**
			 * @brief Runs the client
			 */
			void run();

			/**
			 * @brief Closes the client
			 * @param signal The signal to close the client
			 */
            static void closeJetpackClient(int signal);

            static std::mutex isRunningMutex;
            static bool isRunning;



		private:

			/**
			 * @brief Enumeration for music state
			 */
            enum class MusicState {
				PLAYING,
                PAUSED,
                STOPPED,
                NONE
            };

			/* Initialization functions */

			/**
			 * @brief Checks the command line arguments
			 * @param ac Number of command line arguments
			 * @param av Array of command line arguments
			 */
			void _checkArgs(int ac, char **av);

			/**
			 * @brief Initializes the commands
			 */
			void _initCommands();

			/**
			 * @brief Initializes the game information
			 */
			void _initGameInformation();

			/**
			 * @brief Initializes the client
			 */
			void _initClient();

			/**
			 * @brief Initializes the FX
			 */
			void _initFx();

			/**
			 * @brief Initializes the music
			 */
            void _initMusic();

			/**
			 * @brief Initializes the graphical elements
			 */
			void _initGraphicalElements();

			/**
			 * @brief Initializes the sprits
			 */
			void _initElements();

			/**
			 * @brief Initializes the SFML
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
			 * @brief Updates the game state
			 */
            void _updateFromResponse();

			/**
			 * @brief Updates the animation
			 * @param deltaTime The time since the last update
			 */
			void _updateAnimation(float deltaTime);

			/**
			 * @brief Updates
			 * @param deltaTime The time since the last update
			 */
            void _update(float deltaTime);

			/**
			 * @brief Draws the elements on the screen
			 * @param deltaTime The time since the last update
			 */
            void _drawElements(float deltaTime);

			/**
			 * @brief Analyzes the event
			 */
			void _analyseEvent();

        protected:
			/* Command functions */

			/**
			 * @brief Executes the exit command
			 * @param command The command to execute
			 */
            void executeExit(std::vector<std::string> &command);

			/* Response handler functions */

			/**
			 * @brief Handles the command ID
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandId(const int &code, const std::string &message);

			/**
			 * @brief Handles the command MAP
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandMap(const int &code, const std::string &message);

			/**
			 * @brief Handles the command PSEUDO
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandPseudo(const int &code, const std::string &message);

			/**
			 * @brief Handles the command MOVE
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandMove(const int &code, const std::string &message);

			/**
			 * @brief Handles the command CLIENT_NB
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandClientsNb(const int &code, const std::string &message);

			/**
			 * @brief Handles the command CLIENTS_STATS
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandClientsStats(const int &code, const std::string &message);

			/**
			 * @brief Handles the command CLIENTS_POSITIONS
			 * @param code The command code
			 * @param message The message to handle
			 */
			void handleCommandClientsPositions(const int &code, const std::string &message);

        private:
			/* Client information */
			std::string _ip;
			std::string _port;
			std::unique_ptr<Socket> _client_socket;
			struct sockaddr_in _client;
            std::mutex _commands_queue_mutex;
            std::queue<std::vector<std::string>> _commands_queue;
            std::mutex _response_queue_mutex;
            std::queue<response_t> _response_queue;

			/* Game information */
			bool _gameStarted = false;
			std::size_t _id;
			std::vector<std::string> _map;
			std::size_t _nb_players = 0;
            std::map<size_t, std::unique_ptr<Player>> _players;


			/* Graphical elements */
			#define WINDOW_WIDTH 1280.0
			#define WINDOW_HEIGHT 720.0
			sf::RenderWindow _window;
			#define NB_LINES _map.size()
			#define RATIO (WINDOW_HEIGHT / static_cast<float>(NB_LINES))

				/* Text */
				sf::Font _font;
				sf::Text _text;

				/* Music */
				sf::Music _mainMenuMusic;
				MusicState _mainMenuMusicState = MusicState::NONE;

				sf::Music _mainMusic;
				MusicState _musicState = MusicState::NONE;

				/* Fx */
				sf::SoundBuffer _jetpackSoundStartBuffer;
				sf::Sound _jetpackSoundStart;
				MusicState _jetpackSoundStartState = MusicState::NONE;

				sf::SoundBuffer _jetpackSoundStopBuffer;
				sf::Sound _jetpackSoundStop;
				MusicState _jetpackSoundStopState = MusicState::NONE;

				sf::SoundBuffer _jetpackSoundDownBuffer;
				sf::Sound _jetpackSoundDown;
				MusicState _jetpackSoundDownState = MusicState::NONE;

				sf::SoundBuffer _jetpackSoundUpBuffer;
				sf::Sound _jetpackSoundUp;
				MusicState _jetpackSoundUpState = MusicState::NONE;

				sf::SoundBuffer _coinSoundBuffer;
				sf::Sound _coinSound;
				MusicState _coinSoundState = MusicState::NONE;

				sf::SoundBuffer _zappedSoundBuffer;
				sf::Sound _zappedSound;
				MusicState _zappedSoundState = MusicState::NONE;

				/* Background */
				sf::Texture _background_texture;
				sf::Sprite _background_sprite;
				float _background_size;
				float _background_pos = 0.f;
				#define BACKGROUND_SPEED 100.f

				/* Player */
				sf::Texture _player_texture;
				sf::Sprite _player_sprite;
				bool _jetpack = false;
				Player::PlayerState _curent_state = Player::PlayerState::NORMAL;

				/* Coin */
				sf::Texture _coin_texture;
				sf::Sprite _coin_sprite;
				Animation _coin_animation;
                std::vector<std::unique_ptr<Coin>> _coins;

				/* Zappe */
				sf::Texture _zapper_texture;
				sf::Sprite _zapper_sprite;
				Animation _zapper_animation;
                std::vector<std::unique_ptr<Zapper>> _zappers;

			/* Commands */
			std::unordered_map<std::string, std::function<void(std::vector<std::string> &command)>> _commands;
	};
}

#endif /* CLIENT_HPP_ */
