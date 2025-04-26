/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Socket.cpp
*/
/**
 * @file Socket.cpp
 * @brief The Socket.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "utils/Socket.hpp"

namespace Jetpack {
    /**
     * @brief Constructor for Socket class
     * @param domain The domain of the socket
     * @param type The type of the socket
     * @param protocol The protocol of the socket
     * @throw JetpackError If the socket creation fails
     */
    Socket::Socket(int domain, int type, int protocol)
    {
        DEBUG << "Socket creation";
        _sockfd = socket(domain, type, protocol);
        if (_sockfd == -1)
            throw JetpackError("Socket creation failed: " + std::string(strerror(errno)));
    }

    /**
     * @brief Constructor for Socket class
     * @param sockfd The socket file descriptor
     */
    Socket::Socket(int sockfd)
    {
        DEBUG << "Socket creation";
        _sockfd = sockfd;
    }

    /**
     * @brief Deleted copy constructor
     * @param other The other Socket object to copy from
     */
    Socket::~Socket()
    {
        DEBUG << "Socket destruction";
        close(_sockfd);
    }

    /**
     * @brief Gets the socket file descriptor
     * @return The socket file descriptor
     */
    int Socket::getSocket() const
    {
        return _sockfd;
    }

    /**
     * @brief Sets the socket file descriptor
     * @param sockfd The socket file descriptor
     */
    void Socket::operator()(int sockfd)
    {
        _sockfd = sockfd;
    }

    /**
     * @brief Sets the socket file descriptor
     * @param sockfd The socket file descriptor
     */
    void Socket::operator=(int sockfd)
    {
        _sockfd = sockfd;
    }

    /**
     * @brief Compares the socket file descriptor
     * @param sockfd The socket file descriptor
     * @return True if the socket file descriptor is equal to the current one
     * and False if the socket file descriptor is not equal to the current one
     */
    bool Socket::operator==(int sockfd) const
    {
        return _sockfd == sockfd;
    }
}