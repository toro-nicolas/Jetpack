/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Pseudo.cpp
*/
/**
 * @file Pseudo.cpp
 * @brief The Pseudo.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "server/ServerClient.hpp"

namespace Jetpack {
    /**
     * @brief Execute the pseudo command
     * @param client_fd The file descriptor of the client
     * @param command The command to execute
     */
    void Server::executePseudo(int client_fd, std::vector<std::string> &command)
    {
        DEBUG << "Execute pseudo";
        if (command.size() != 2) {
            ERROR << "pseudo: Invalid number of arguments.";
            sendResponse(client_fd, CMD_PSEUDO_ID, CODE_ERROR + CODE_PERSONNAL, "Invalid number of arguments.");
            return;
        }
        if (command[1].find_first_of(INVALID_PSEUDO_CHARACTERS) != std::string::npos) {
            ERROR << "pseudo: Invalid pseudo.";
            sendResponse(client_fd, CMD_PSEUDO_ID, CODE_ERROR + CODE_PERSONNAL, "Invalid pseudo.");
            return;
        }
        _clients[client_fd]->setPseudo(command[1]);
        sendResponse(client_fd,  CMD_PSEUDO_ID, CODE_OK + CODE_PERSONNAL, "Pseudo set to " + command[1]);
    }
}