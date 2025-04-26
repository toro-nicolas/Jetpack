/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Game.cpp
*/
/**
 * @file Game.cpp
 * @brief The Game.cpp
 * @author Nicolas TORO
 */

#include "server/ServerClient.hpp"

namespace Jetpack {
    /**
     * @brief Checks if the player is on the map
     * @param x The x position of the player
     * @param y The y position of the player
     * @param c The character to check
     * @return True if the player is on the map, false otherwise
     */
    bool Server::_isPlayerOn(const double &x, const double &y, const char c) const
    {
        return
            _map[std::floor(y)][std::floor(x)] == c ||
            _map[std::ceil(y)][std::floor(x)] == c ||
            _map[std::floor(y)][std::ceil(x)] == c ||
            _map[std::ceil(y)][std::ceil(x)] == c;
    }

    /**
     * @brief Analyse if the client is on a coin
     * and add it to the client coin list
     * @param client The client to analyse
     */
    void Server::_analyseClientOnCoin(Jetpack::Server::Client &client)
    {
        std::vector<std::array<size_t, 2>> coin_pos = {
            {static_cast<size_t>(std::floor(client.getPosition()[1])), static_cast<size_t>(std::floor(client.getPosition()[0]))},
            {static_cast<size_t>(std::ceil(client.getPosition()[1])), static_cast<size_t>(std::floor(client.getPosition()[0]))},
            {static_cast<size_t>(std::floor(client.getPosition()[1])), static_cast<size_t>(std::ceil(client.getPosition()[0]))},
            {static_cast<size_t>(std::ceil(client.getPosition()[1])), static_cast<size_t>(std::ceil(client.getPosition()[0]))}};

        for (const auto &coin : coin_pos) {
            if (std::find(client.getCoinsList().begin(), client.getCoinsList().end(),
            std::array<size_t, 2>{coin[0], coin[1]}) == client.getCoinsList().end()
            && _map[coin[0]][coin[1]] == 'c') {
                client.setScore(client.getScore() + 1);
                client.getCoinsList().push_back({coin[0], coin[1]});
            }
        }
    }

    /**
     * @brief Updates a client (player)
     * @param client The client to update
     * @param delta_time The time since the last frame
     * @param reset_coins True if the coins should be reset
     * and false if not
     */
    void Server::_updatePlayer(Client &client, double &delta_time, bool &reset_coins)
    {
        /* Update speed */
        if (client.useJetpack())
            client.setSpeed(client.getSpeed() + -JETPACK_SPEED * delta_time);
        else
            client.setSpeed(client.getSpeed() + GRAVITY * delta_time);

        /* Update positions	*/
        client.setPosition({_map_x_pos, client.getPosition()[1] + client.getSpeed() * delta_time});
        if (client.getPosition()[1] < MIN_HEIGHT) {
            client.setPosition({client.getPosition()[0], 0});
            client.setSpeed(0);
        }
        if (client.getPosition()[1] > MAX_HEIGHT) {
            client.setPosition({client.getPosition()[0], static_cast<double>(MAX_HEIGHT)});
            client.setSpeed(0);
        }

        /* Check if the player is alive */
        if (_isPlayerOn(client.getPosition()[0], client.getPosition()[1], 'e') ||
        _isPlayerOn(client.getPosition()[0], client.getPosition()[1], 'l') ||
        _isPlayerOn(client.getPosition()[0], client.getPosition()[1], 'm'))
            client.setAlive(false);

        /* Check if a player is on a coin */
        if (reset_coins)
            client.getCoinsList().clear();
        if (client.isAlive())
            _analyseClientOnCoin(client);
    }

    /**
     * @brief Updates the game
     * @note This function is called every frame/poll
     */
    void Server::_updateGame()
    {
        double delta_time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - _last_update).count();
        bool reset_coins = false;
        std::size_t winner_score = 0;
        std::size_t winner_id = 0;

        //DEBUG << "Update game";
        _last_update = std::chrono::high_resolution_clock::now();
        if (_clients.empty()) {
            _map_x_pos = 0;
            return;
        }
        if (_clients.size() > 1) {
            _map_x_pos += PLAYER_SPEED * delta_time;
            if (_map_x_pos >= static_cast<double>(_map[0].size())) {
                if (_infinite_mode) {
                    _map_x_pos -= static_cast<double>(_map[0].size());
                    reset_coins = true;
                } else {
                    for (auto &client : _clients) {
                        client.second->setAlive(false);
                        if (client.second->getScore() > winner_score) {
                            winner_score = client.second->getScore();
                            winner_id = client.first;
                        }
                    }
                    if (winner_id != 0)
                        _clients[winner_id]->setAlive(true);
                }
            }
            for (auto &client : _clients)
                _updatePlayer(*client.second, delta_time, reset_coins);
        }
    }
}