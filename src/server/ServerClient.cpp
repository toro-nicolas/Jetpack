/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Client.cpp
*/
/**
 * @file Client.cpp
 * @brief The Client.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "server/ServerClient.hpp"

namespace Jetpack {
	Server::Client::Client(int socket_fd, struct sockaddr_in client_addr) :
		_socket_fd(socket_fd), _client_addr(client_addr)
	{
		DEBUG << "Server client creation";
        _pseudo = "Player " + std::to_string(socket_fd);
	}

	Server::Client::~Client()
	{
		DEBUG << "Server client destruction";
	}

	Server::Client::Client(const Server::Client &client) : _socket_fd(client._socket_fd), _client_addr(client._client_addr)
	{
		DEBUG << "Server client copy";
		if (this != &client) {
            _pseudo = client._pseudo;
            _position = client._position;
            _score = client._score;
            _alive = client._alive;
            _jetpack = client._jetpack;
            _speed = client._speed;
		}
	}

	Server::Client &Server::Client::operator=(const Server::Client &client)
	{
		DEBUG << "Server client assignation";
		if (this != &client) {
            _pseudo = client._pseudo;
            _position = client._position;
            _score = client._score;
            _alive = client._alive;
            _jetpack = client._jetpack;
            _speed = client._speed;
		}
		return *this;
	}

    const std::string &Server::Client::getNextCommand() const
    {
        return _next_command;
    }

    void Server::Client::setNextCommand(const std::string &nextCommand)
    {
        _next_command = nextCommand;
    }

    const int &Server::Client::getSocketFd() const
    {
        return _socket_fd;
    }

    const struct sockaddr_in &Server::Client::getClientAddr() const
    {
        return _client_addr;
    }

    const std::string &Server::Client::getPseudo() const
    {
        return _pseudo;
    }

    void Server::Client::setPseudo(const std::string &pseudo)
    {
        _pseudo = pseudo;
    }

    const std::array<double, 2> &Server::Client::getPosition() const
    {
        return _position;
    }

    void Server::Client::setPosition(const std::array<double, 2> &position)
    {
        _position = position;
    }

    const std::size_t &Server::Client::getScore() const
    {
        return _score;
    }

    void Server::Client::setScore(std::size_t score)
    {
        _score = score;
    }

    const bool &Server::Client::isAlive() const
    {
        return _alive;
    }

    void Server::Client::setAlive(bool alive)
    {
        _alive = alive;
    }

    const bool &Server::Client::useJetpack() const
    {
        return _jetpack;
    }

    void Server::Client::setJetpack(bool jetpack)
    {
        _jetpack = jetpack;
    }

    const double &Server::Client::getSpeed() const
    {
        return _speed;
    }

    void Server::Client::setSpeed(double speed)
    {
        _speed = speed;
    }

    std::vector<std::array<std::size_t, 2>> &Server::Client::getCoinsList()
    {
        return _coins_list;
    }
}