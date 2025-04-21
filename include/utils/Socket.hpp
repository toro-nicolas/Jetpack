/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Socket.hpp
*/
/**
 * @file Socket.hpp
 * @brief The Socket.hpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#ifndef SOCKET_HPP_
    #define SOCKET_HPP_

    #include "utils/Exception.hpp"
    #include "utils/Logs.hpp"

namespace Jetpack {
    class Socket
    {
        public:
            Socket(int domain, int type, int protocol);
            Socket(int sockfd = -1);
            ~Socket();

            int getSocket() const;
            void operator()(int sockfd);
            void operator=(int sockfd);
            bool operator==(int sockfd) const;

        private:
            int _sockfd;
    };
}

#endif /* SOCKET_HPP_ */
