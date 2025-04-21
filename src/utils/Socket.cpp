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
    Socket::Socket(int domain, int type, int protocol)
    {
        DEBUG << "Socket creation";
        _sockfd = socket(domain, type, protocol);
        if (_sockfd == -1)
            throw JetpackError("Socket creation failed: " + std::string(strerror(errno)));
    }

    Socket::Socket(int sockfd)
    {
        DEBUG << "Socket creation";
        _sockfd = sockfd;
    }

    Socket::~Socket()
    {
        DEBUG << "Socket destruction";
        close(_sockfd);
    }

    int Socket::getSocket() const
    {
        return _sockfd;
    }

    void Socket::operator()(int sockfd)
    {
        _sockfd = sockfd;
    }

    void Socket::operator=(int sockfd)
    {
        _sockfd = sockfd;
    }

    bool Socket::operator==(int sockfd) const
    {
        return _sockfd == sockfd;
    }
}