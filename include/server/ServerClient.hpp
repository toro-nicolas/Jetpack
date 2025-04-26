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

	#include "server/Server.hpp"

namespace Jetpack {
    /**
     * @class Server::Client
     * @brief A class that represents a client connected to the server
     */
	class Server::Client {
		public:
            /* Constructor and destructor */

            /**
             * @brief Constructor for Client class
             * @param socket_fd The socket file descriptor of the client
             * @param client_addr The address of the client
             * @param start_y_pos The starting y position of the client
             */
			Client(int socket_fd, struct sockaddr_in client_addr, double start_y_pos);
            /**
             * @brief Destructor for Client class
             */
			~Client();
            /**
             * @brief Copy constructor for Client class
             * @param client The Client object to copy from
             */
			Client(const Client &);
            /**
             * @brief Assignment operator for Client class
             * @param client The Client object to assign from
             * @return Reference to the current object
             */
			Client &operator=(const Client &);



			/* Getter and Setter for client information */

            /**
             * @brief Gets the next command to be executed
             * @return The next command to be executed
             */
			const std::string &getNextCommand() const;
            /**
             * @brief Sets the next command to be executed
             * @param nextCommand The next command to be executed
             */
			void setNextCommand(const std::string &nextCommand);
            /**
             * @brief Gets the socket file descriptor
             * @return The socket file descriptor
             */
			const int &getSocketFd() const;
            /**
             * @brief Gets the client address
             * @return The client address
             */
			const struct sockaddr_in &getClientAddr() const;



            /* Getter and Setter for client player */

            /**
             * @brief Gets the pseudo of the client
             * @return The pseudo of the client
             */
            const std::string &getPseudo() const;
            /**
             * @brief Sets the pseudo of the client
             * @param pseudo The pseudo of the client
             */
            void setPseudo(const std::string &pseudo);
            /**
             * @brief Gets the position of the client
             * @return The position of the client
             */
            const std::array<double, 2> &getPosition() const;
            /**
             * @brief Sets the position of the client
             * @param position The position of the client
             */
            void setPosition(const std::array<double, 2> &position);
            /**
             * @brief Gets the score of the client
             * @return The score of the client
             */
            const std::size_t &getScore() const;
            /**
             * @brief Sets the score of the client
             * @param score The score of the client
             */
            void setScore(std::size_t score);
            /**
             * @brief Gets the alive status of the client
             * @return The alive status of the client
             */
            const bool &isAlive() const;
            /**
             * @brief Sets the alive status of the client
             * @param alive The alive status of the client
             */
            void setAlive(bool alive);
            /**
             * @brief Gets the jetpack status of the client
             * @return The jetpack status of the client
             */
            const bool &useJetpack() const;
            /**
             * @brief Sets the jetpack status of the client
             * @param jetpack The jetpack status of the client
             */
            void setJetpack(bool jetpack);
            /**
             * @brief Gets the speed of the client
             * @return The speed of the client
             */
            const double &getSpeed() const;
            /**
             * @brief Sets the speed of the client
             * @param speed The speed of the client
             */
            void setSpeed(double speed);
            /**
             * @brief Gets the list of coins collected by the client
             * @return The list of coins collected by the client
             */
            std::vector<std::array<std::size_t, 2>> &getCoinsList();



		private:
			std::string _next_command; /* The next command to be executed */
			const int _socket_fd; /* The socket file descriptor */
			const struct sockaddr_in _client_addr; /* The address of the client */

            std::string _pseudo; /* The pseudo of the client */
            std::array<double, 2> _position = {0.0, 0.0}; /* The position of the client */
            std::size_t _score = 0; /* The score of the client */
            bool _alive = true; /* The live status of the client */
            bool _jetpack = false; /* The jetpack status of the client */
            double _speed = 0.0; /* The speed of the client */
            std::vector<std::array<std::size_t, 2>> _coins_list; /* The list of coins collected by the client */
	};
}

#endif /* CLIENT_HPP_ */
