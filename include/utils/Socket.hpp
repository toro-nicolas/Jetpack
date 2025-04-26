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
    /**
     * @class Socket
     * @brief An encapsulation of the socket file descriptor
     */
    class Socket
    {
        public:
            /**
             * @brief Constructor for Socket class
             * @param domain The domain of the socket
             * @param type The type of the socket
             * @param protocol The protocol of the socket
             * @throw JetpackError If the socket creation fails
             */
            Socket(int domain, int type, int protocol);
            /**
             * @brief Constructor for Socket class
             * @param sockfd The socket file descriptor
             */
            Socket(int sockfd = -1);
            /**
             * @brief Deleted copy constructor
             * @param other The other Socket object to copy from
             */
            ~Socket();



            /**
             * @brief Gets the socket file descriptor
             * @return The socket file descriptor
             */
            int getSocket() const;
            /**
             * @brief Sets the socket file descriptor
             * @param sockfd The socket file descriptor
             */
            void operator()(int sockfd);
            /**
             * @brief Sets the socket file descriptor
             * @param sockfd The socket file descriptor
             */
            void operator=(int sockfd);
            /**
             * @brief Compares the socket file descriptor
             * @param sockfd The socket file descriptor
             * @return True if the socket file descriptor is equal to the current one
             * and False if the socket file descriptor is not equal to the current one
             */
            bool operator==(int sockfd) const;



        private:
            int _sockfd; /* The socket file descriptor */
    };
}

#endif /* SOCKET_HPP_ */
