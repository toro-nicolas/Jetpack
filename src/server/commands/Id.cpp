/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Id.cpp
*/
/**
 * @file Id.cpp
 * @brief The Id.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "server/ServerClient.hpp"

namespace Jetpack {
    /**
     * @brief Execute the id command
     * @param client_fd The file descriptor of the client
     * @param command The command to execute
     */
    void Server::executeId(int client_fd, std::vector<std::string> &command)
    {
        DEBUG << "Execute ID";
        if (command.size() != 1) {
            ERROR << "ID: Invalid number of arguments.";
            sendResponse(client_fd, CMD_ID_ID, CODE_ERROR + CODE_GAME, "Invalid number of arguments.");
            return;
        }
        sendResponse(client_fd, CMD_ID_ID, CODE_OK + CODE_GAME, std::to_string(client_fd));
    }
}