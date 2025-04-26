/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The ClientsStats.cpp
*/
/**
 * @file ClientsStats.cpp
 * @brief The ClientsStats.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "client/Client.hpp"

namespace Jetpack {
    /**
     * @brief Handles the response of the command CLIENTS_STATS
     * @param code The command code
     * @param message The message to handle
     */
	void Client::handleCommandClientsStats(const int &code, const std::string &message)
	{
        std::size_t current_id;
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
                current_id = std::stoul(client_data[0]);
				if (_players.find(current_id) == _players.end())
					_players[current_id] = std::make_unique<Player>(current_id, _player_texture.getSize());
				_players[current_id]->setPseudo(client_stats[0]);
				_players[current_id]->setAlive(client_stats[1] == "1");
				_players[current_id]->setScore(std::stoul(client_stats[2]));
				DEBUG << current_id << ": setPseudo: " << _players[current_id]->getPseudo();
				DEBUG << current_id << ": setAlive: " << _players[current_id]->isAlive();
				DEBUG << current_id << ": setScore: " << _players[current_id]->getScore();
				players_id.insert(current_id);
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
