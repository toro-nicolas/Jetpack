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
	class Server::Client {
		public:
			Client(int socket_fd, struct sockaddr_in client_addr);
			~Client();
			Client(const Client &);
			Client &operator=(const Client &);

			/* Getter and Setter for client information */
			const std::string &getNextCommand() const;
			void setNextCommand(const std::string &nextCommand);
			const int &getSocketFd() const;
			const struct sockaddr_in &getClientAddr() const;

            /* Getter and Setter for client player */
            const std::string &getPseudo() const;
            void setPseudo(const std::string &pseudo);
            const std::array<double, 2> &getPosition() const;
            void setPosition(const std::array<double, 2> &position);
            const std::size_t &getScore() const;
            void setScore(std::size_t score);
            const bool &isAlive() const;
            void setAlive(bool alive);
            const bool &useJetpack() const;
            void setJetpack(bool jetpack);
            const double &getSpeed() const;
            void setSpeed(double speed);
            std::vector<std::array<std::size_t, 2>> &getCoinsList();


		private:
			std::string _next_command;
			const int _socket_fd;
			const struct sockaddr_in _client_addr;

            std::string _pseudo;
            std::array<double, 2> _position = {0.0, 0.0};
            std::size_t _score = 0;
            bool _alive = true;
            bool _jetpack = false;
            double _speed = 0.0;
            std::vector<std::array<std::size_t, 2>> _coins_list;
	};
}

#endif /* CLIENT_HPP_ */
