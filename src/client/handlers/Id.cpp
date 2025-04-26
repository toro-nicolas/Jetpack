/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Id.cpp
*/
/**
 * @file Id.cpp
 * @brief The Id.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
    /**
     * @brief Handles the response of the command ID
     * @param code The command code
     * @param message The message to handle
     */
	void Client::handleCommandId(const int &code, const std::string &message)
	{
		DEBUG << "Handle command ID";
        if (code != CODE_OK + CODE_GAME) {
            ERROR << "ID: Invalid or negative response.";
            return;
        }
		try {
			_id = std::stoul(message);
			DEBUG << "ID: " << _id;
		} catch (const std::exception &e) {
			ERROR << "id: Invalid argument.";
		}
	}
}
