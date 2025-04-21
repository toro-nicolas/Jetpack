/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Move.cpp
*/
/**
 * @file Move.cpp
 * @brief The Move.cpp
 * @author Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
	void Client::handleCommandMove(const int &code, const std::string &message)
	{
		DEBUG << "Handle command MOVE";
        if (code != CODE_OK + CODE_PERSONNAL) {
            ERROR << "MOVE: Invalid or negative response.";
            return;
        }
		DEBUG << "Player moved";
	}
}
