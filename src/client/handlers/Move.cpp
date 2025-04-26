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

#include "client/Client.hpp"
#include "utils/Jetpack.hpp"

namespace Jetpack {
    /**
     * @brief Handles the response of the command MOVE
     * @param code The command code
     * @param message The message to handle
     */
	void Client::handleCommandMove(const int &code, UNUSED const std::string &message)
	{
		DEBUG << "Handle command MOVE";
        if (code != CODE_OK + CODE_PERSONNAL) {
            ERROR << "MOVE: Invalid or negative response.";
            return;
        }
		DEBUG << "Player moved";
	}
}
