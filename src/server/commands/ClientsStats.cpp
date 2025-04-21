/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The ClientsStats.cpp
*/
/**
 * @file ClientsStats.cpp
 * @brief The ClientsStats.cpp
 * @author Nicolas TORO
 */

#include "server/ServerClient.hpp"

namespace Jetpack {
    void Server::executeClientsStats(int client_fd, std::vector<std::string> &command)
    {
        DEBUG << "Execute clients Stats";
        if (command.size() != 1) {
            ERROR << "clients_Stats: Invalid number of arguments.";
            sendResponse(client_fd, CMD_CLIENTS_STATS_ID, CODE_ERROR + CODE_CLIENTS, "Invalid number of arguments.");
            return;
        }
        std::string Stats;
        for (const auto &client : _clients) {
            if (!Stats.empty())
                Stats += "|";
            Stats += std::to_string(client.first) + ":" +
                client.second->getPseudo() + "," +
                std::to_string(client.second->isAlive()) + "," +
                std::to_string(client.second->getScore());
        }
        sendResponse(client_fd, CMD_CLIENTS_STATS_ID, CODE_OK + CODE_CLIENTS, Stats);
    }
}