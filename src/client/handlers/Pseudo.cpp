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

#include "client/Client.hpp"
#include "utils/Jetpack.hpp"

namespace Jetpack {
    /**
     * @brief Handles the response of the command PSEUDO
     * @param code The command code
     * @param message The message to handle
     */
	void Client::handleCommandPseudo(const int &code, UNUSED const std::string &message)
	{
		DEBUG << "Handle command PSEUDO";
        if (code != CODE_OK + CODE_PERSONNAL) {
            ERROR << "PSEUDO: Invalid or negative response.";
            return;
        }
		DEBUG << "Pseudo changed";
	}
}
