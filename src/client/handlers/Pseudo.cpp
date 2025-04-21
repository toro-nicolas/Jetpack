/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Pseudo.cpp
*/
/**
 * @file Pseudo.cpp
 * @brief The Pseudo.cpp
 * @author Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
	void Client::handleCommandPseudo(const int &code, const std::string &message)
	{
		DEBUG << "Handle command PSEUDO";
        if (code != CODE_OK + CODE_PERSONNAL) {
            ERROR << "PSEUDO: Invalid or negative response.";
            return;
        }
		DEBUG << "Pseudo changed";
	}
}
