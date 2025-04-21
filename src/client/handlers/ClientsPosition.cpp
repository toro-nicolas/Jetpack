/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The ClientsPosition.cpp
*/
/**
 * @file ClientsPosition.cpp
 * @brief The ClientsPosition.cpp
 * @author Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
	void Client::handleCommandClientsPositions(const int &code, const std::string &message)
	{
		std::set<std::size_t> players_id;
		std::vector<std::string> clients_positions;
		std::vector<std::string> client_data;
		std::vector<std::string> client_pos;


		DEBUG << "Handle command CLIENTS_POSITIONS";
        if (code != CODE_OK + CODE_CLIENTS) {
            ERROR << "CLIENTS_POSITIONS: Invalid or negative response.";
            return;
        }
		try {
			clients_positions = stringToVector(message, "|");

			for (std::size_t index = 0; index < clients_positions.size(); ++index) {
				client_data = stringToVector(clients_positions[index], ":");
				if (client_data.size() != 2)
					throw std::invalid_argument("Invalid number of arguments.");
				client_pos = stringToVector(client_data[1], ",");
				if (client_pos.size() != 2)
					throw std::invalid_argument("Invalid number of arguments.");
				if (_players.find(std::stoul(client_data[0])) == _players.end())
					_players[std::stoul(client_data[0])] = std::make_unique<Player>(std::stoul(client_data[0]), _player_texture.getSize());
				_players[std::stoul(client_data[0])]->setPosition({std::stof(client_pos[0]), std::stof(client_pos[1])});
				players_id.insert(std::stoul(client_data[0]));
			}
			for (auto it = _players.begin(); it != _players.end(); ) {
				if (players_id.find(it->first) == players_id.end()) {
					DEBUG << it->second->getPseudo() << ": disconnected";
					it = _players.erase(it);  // erase() renvoie l'itérateur suivant
				} else {
					++it;
				}
			}
			DEBUG << "CLIENTS_POSITIONS: " << message;
		} catch (const std::exception &e) {
			ERROR << "clients_positions: Invalid argument.";
		}
	}
}
