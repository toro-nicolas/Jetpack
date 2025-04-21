/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Pseudo.cpp
*/
/**
 * @file Pseudo.cpp
 * @brief The Pseudo.cpp
 * @author Nicolas TORO
 */

#include "server/ServerClient.hpp"

namespace Jetpack {
    void Server::executePseudo(int client_fd, std::vector<std::string> &command)
    {
        DEBUG << "Execute pseudo";
        if (command.size() != 2) {
            ERROR << "pseudo: Invalid number of arguments.";
            sendResponse(client_fd, CMD_PSEUDO_ID, CODE_ERROR + CODE_PERSONNAL, "Invalid number of arguments.");
            return;
        }
        _clients[client_fd]->setPseudo(command[1]);
        sendResponse(client_fd,  CMD_PSEUDO_ID, CODE_OK + CODE_PERSONNAL, "Pseudo set to " + command[1]);
    }
}