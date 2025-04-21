/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The ClientsNb.cpp
*/
/**
 * @file ClientsNb.cpp
 * @brief The ClientsNb.cpp
 * @author Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
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
