/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The ServerClient.cpp
*/
/**
 * @file ServerClient.cpp
 * @brief The ServerClient.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "server/ServerClient.hpp"

namespace Jetpack {
    /**
     * @brief Constructor for Client class
     * @param socket_fd The socket file descriptor of the client
     * @param client_addr The address of the client
     * @param start_y_pos The starting y position of the client
     */
	Server::Client::Client(int socket_fd, struct sockaddr_in client_addr, double start_y_pos) :
		_socket_fd(socket_fd), _client_addr(client_addr)
	{
		DEBUG << "Server client creation";
        _pseudo = "Player " + std::to_string(socket_fd - START_FD + 1);
        _position[1] = start_y_pos;
	}

    /**
     * @brief Destructor for Client class
     */
	Server::Client::~Client()
	{
		DEBUG << "Server client destruction";
	}

    /**
     * @brief Copy constructor for Client class
     * @param client The Client object to copy from
     */
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
            _coins_list = client._coins_list;
		}
	}

    /**
     * @brief Assignment operator for Client class
     * @param client The Client object to assign from
     * @return Reference to the current object
     */
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
            _coins_list = client._coins_list;
		}
		return *this;
	}

    /**
     * @brief Gets the next command to be executed
     * @return The next command to be executed
     */
    const std::string &Server::Client::getNextCommand() const
    {
        return _next_command;
    }

    /**
     * @brief Sets the next command to be executed
     * @param nextCommand The next command to be executed
     */
    void Server::Client::setNextCommand(const std::string &nextCommand)
    {
        _next_command = nextCommand;
    }

    /**
     * @brief Gets the socket file descriptor
     * @return The socket file descriptor
     */
    const int &Server::Client::getSocketFd() const
    {
        return _socket_fd;
    }

    /**
     * @brief Gets the client address
     * @return The client address
     */
    const struct sockaddr_in &Server::Client::getClientAddr() const
    {
        return _client_addr;
    }

    /**
     * @brief Gets the pseudo of the client
     * @return The pseudo of the client
     */
    const std::string &Server::Client::getPseudo() const
    {
        return _pseudo;
    }

    /**
     * @brief Sets the pseudo of the client
     * @param pseudo The pseudo of the client
     */
    void Server::Client::setPseudo(const std::string &pseudo)
    {
        _pseudo = pseudo;
    }

    /**
     * @brief Gets the position of the client
     * @return The position of the client
     */
    const std::array<double, 2> &Server::Client::getPosition() const
    {
        return _position;
    }

    /**
     * @brief Sets the position of the client
     * @param position The position of the client
     */
    void Server::Client::setPosition(const std::array<double, 2> &position)
    {
        _position = position;
    }

    /**
     * @brief Gets the score of the client
     * @return The score of the client
     */
    const std::size_t &Server::Client::getScore() const
    {
        return _score;
    }

    /**
     * @brief Sets the score of the client
     * @param score The score of the client
     */
    void Server::Client::setScore(std::size_t score)
    {
        _score = score;
    }

    /**
     * @brief Gets the alive status of the client
     * @return The alive status of the client
     */
    const bool &Server::Client::isAlive() const
    {
        return _alive;
    }

    /**
     * @brief Sets the alive status of the client
     * @param alive The alive status of the client
     */
    void Server::Client::setAlive(bool alive)
    {
        _alive = alive;
        if (!alive)
            _jetpack = false;
    }

    /**
     * @brief Gets the jetpack status of the client
     * @return The jetpack status of the client
     */
    const bool &Server::Client::useJetpack() const
    {
        return _jetpack;
    }

    /**
     * @brief Sets the jetpack status of the client
     * @param jetpack The jetpack status of the client
     */
    void Server::Client::setJetpack(bool jetpack)
    {
        _jetpack = jetpack;
    }

    /**
     * @brief Gets the speed of the client
     * @return The speed of the client
     */
    const double &Server::Client::getSpeed() const
    {
        return _speed;
    }

    /**
     * @brief Sets the speed of the client
     * @param speed The speed of the client
     */
    void Server::Client::setSpeed(double speed)
    {
        _speed = speed;
    }

    /**
     * @brief Gets the list of coins collected by the client
     * @return The list of coins collected by the client
     */
    std::vector<std::array<std::size_t, 2>> &Server::Client::getCoinsList()
    {
        return _coins_list;
    }
}