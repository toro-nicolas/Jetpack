/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The ClientsNb.cpp
*/
/**
 * @file ClientsNb.cpp
 * @brief The ClientsNb.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "server/Server.hpp"

namespace Jetpack {
    /**
     * @brief Execute the clients nb command
     * @param client_fd The file descriptor of the client
     * @param command The command to execute
     */
    void Server::executeClientsNb(int client_fd, std::vector<std::string> &command)
    {
        DEBUG << "Execute clients nb";
        if (command.size() != 1) {
            ERROR << "clients_nb: Invalid number of arguments.";
            sendResponse(client_fd, CMD_CLIENTS_NB_ID, CODE_ERROR + CODE_CLIENTS, "Invalid number of arguments.");
            return;
        }
        sendResponse(client_fd, CMD_CLIENTS_NB_ID, CODE_OK + CODE_CLIENTS, std::to_string(_clients.size()));
    }
}