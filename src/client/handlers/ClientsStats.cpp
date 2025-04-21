/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The ClientsStats.cpp
*/
/**
 * @file ClientsStats.cpp
 * @brief The ClientsStats.cpp
 * @author Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
	void Client::handleCommandClientsStats(const int &code, const std::string &message)
	{
		std::set<std::size_t> players_id;
		std::vector<std::string> clients_stats;
		std::vector<std::string> client_data;
		std::vector<std::string> client_stats;

		DEBUG << "Handle command CLIENTS_STATS";
        if (code != CODE_OK + CODE_CLIENTS) {
            ERROR << "CLIENTS_STATS: Invalid or negative response.";
            return;
        }
		try {
			clients_stats = stringToVector(message, "|");
			for (std::size_t index = 0; index < clients_stats.size(); ++index) {
				client_data = stringToVector(clients_stats[index], ":");
				if (client_data.size() != 2)
					throw std::invalid_argument("Invalid number of arguments.");
				client_stats = stringToVector(client_data[1], ",");
				if (client_stats.size() != 3)
					throw std::invalid_argument("Invalid number of arguments.");
				if (_players.find(std::stoul(client_data[0])) == _players.end())
					_players[std::stoul(client_data[0])] = std::make_unique<Player>(std::stoul(client_data[0]), _player_texture.getSize());
				_players[std::stoul(client_data[0])]->setPseudo(client_stats[0]);
				_players[std::stoul(client_data[0])]->setAlive(client_stats[1] == "1");
				_players[std::stoul(client_data[0])]->setScore(std::stoul(client_stats[2]));
				DEBUG << std::stoul(client_data[0]) << ": setPseudo: " << _players[std::stoul(client_data[0])]->getPseudo();
				DEBUG << std::stoul(client_data[0]) << ": setAlive: " << _players[std::stoul(client_data[0])]->isAlive();
				DEBUG << std::stoul(client_data[0]) << ": setScore: " << _players[std::stoul(client_data[0])]->getScore();
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
		} catch (const std::exception &e) {
			ERROR << "clients_stats: Invalid argument.";
		}
	}
}
