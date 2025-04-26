/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Move.cpp
*/
/**
 * @file Move.cpp
 * @brief The Move.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "server/ServerClient.hpp"

namespace Jetpack {
    /**
     * @brief Execute the move command
     * @param client_fd The file descriptor of the client
     * @param command The command to execute
     */
    void Server::executeMove(int client_fd, std::vector<std::string> &command)
    {
        DEBUG << "Execute move";
        if (command.size() != 2) {
            ERROR << "move: Invalid number of arguments.";
            sendResponse(client_fd, CMD_MOVE_ID, CODE_ERROR + CODE_PERSONNAL, "Invalid number of arguments.");
            return;
        }
        if (!_clients[client_fd]->isAlive()) {
            ERROR << "move: Player is dead.";
            sendResponse(client_fd, CMD_MOVE_ID, CODE_ERROR + CODE_PERSONNAL, "Client is dead.");
            return;
        }
        if (command[1] == "up" || command[1] == "UP") {
            _clients[client_fd]->setJetpack(true);
            //_clients[client_fd]->setSpeed(0.0);
            sendResponse(client_fd, CMD_MOVE_ID, CODE_OK + CODE_PERSONNAL, "Jetpack ON.");
        } else if (command[1] == "down" || command[1] == "DOWN") {
            _clients[client_fd]->setJetpack(false);
            //_clients[client_fd]->setSpeed(0.0);
            sendResponse(client_fd, CMD_MOVE_ID, CODE_OK + CODE_PERSONNAL, "Jetpack OFF.");
        } else {
            ERROR << "move: Invalid argument.";
            sendResponse(client_fd, CMD_MOVE_ID, CODE_ERROR + CODE_PERSONNAL, "Invalid argument.");
        }
    }
}