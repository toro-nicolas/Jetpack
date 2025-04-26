/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Map.cpp
*/
/**
 * @file Map.cpp
 * @brief The Map.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "server/Server.hpp"

namespace Jetpack {
    /**
     * @brief Execute the map command
     * @param client_fd The file descriptor of the client
     * @param command The command to execute
     */
    void Server::executeMap(int client_fd, std::vector<std::string> &command)
    {
        std::string map;

        DEBUG << "Execute map";
        if (command.size() != 1) {
            ERROR << "map: Invalid number of arguments.";
            sendResponse(client_fd, CMD_MAP_ID, CODE_ERROR + CODE_GAME, "Invalid number of arguments.");
            return;
        }
        for (const auto &line : _map) {
            if (!map.empty())
                map += "|";
            map += line;
        }
        sendResponse(client_fd, CMD_MAP_ID, CODE_OK + CODE_GAME, map);
    }
}