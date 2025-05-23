/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Exit.cpp
*/
/**
 * @file Exit.cpp
 * @brief The Exit.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
    /**
     * @brief Executes the exit command
     * @param command The command to execute
     */
    void Client::executeExit(std::vector<std::string> &command)
    {
        DEBUG << "Execute EXIT";
        if (command.size() != 1) {
            ERROR << "exit: Invalid number of arguments.";
            return;
        }
        std::lock_guard<std::mutex> lock(isRunningMutex);
        isRunning = false;
    }
}