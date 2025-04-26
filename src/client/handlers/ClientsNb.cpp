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

#include "client/Client.hpp"

namespace Jetpack {
    /**
     * @brief Handles the response of the command CLIENT_NB
     * @param code The command code
     * @param message The message to handle
     */
	void Client::handleCommandClientsNb(const int &code, const std::string &message)
	{
		DEBUG << "Handle command CLIENTS_NB";
        if (code != CODE_OK + CODE_CLIENTS) {
            ERROR << "CLIENTS_NB: Invalid or negative response.";
            return;
        }
		try {
			_nb_players = std::stoul(message);
			DEBUG << "CLIENTS_NB: " << _nb_players;
		} catch (const std::exception &e) {
			ERROR << "clients_nb: Invalid argument.";
		}
	}
}
