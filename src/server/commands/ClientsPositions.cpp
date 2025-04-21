/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The ClientsPositions.cpp
*/
/**
 * @file ClientsPositions.cpp
 * @brief The ClientsPositions.cpp
 * @author Nicolas TORO
 */

#include "server/ServerClient.hpp"

namespace Jetpack {
    void Server::executeClientsPositions(int client_fd, std::vector<std::string> &command)
    {
        std::string positions;

        DEBUG << "Execute clients positions";
        if (command.size() != 1) {
            ERROR << "clients_positions: Invalid number of arguments.";
            sendResponse(client_fd, CMD_CLIENTS_POSITIONS_ID, CODE_ERROR + CODE_CLIENTS, "Invalid number of arguments.");
            return;
        }
        for (const auto &client : _clients) {
            if (!positions.empty())
                positions += "|";
            positions += std::to_string(client.first) + ":" +
                std::to_string(client.second->getPosition()[0]) + "," + std::to_string(client.second->getPosition()[1]);
        }
        sendResponse(client_fd, CMD_CLIENTS_POSITIONS_ID, CODE_OK + CODE_CLIENTS, positions);
    }
}