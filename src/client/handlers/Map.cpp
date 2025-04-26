/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Map.cpp
*/
/**
 * @file Map.cpp
 * @brief The Map.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "client/Client.hpp"
#include <memory>

namespace Jetpack {
    /**
     * @brief Handles the response of the command MAP
     * @param code The command code
     * @param message The message to handle
     */
	void Client::handleCommandMap(const int &code, const std::string &message)
	{
		DEBUG << "Handle command MAP";
        if (code != CODE_OK + CODE_GAME) {
            ERROR << "MAP: Invalid or negative response.";
            return;
        }
		try {
			_map = stringToVector(message, "|");
            _coins.clear();
            _traps.clear();
            for (std::size_t row = 0; row < _map.size(); ++row) {
                for (std::size_t col = 0; col < _map[row].size(); ++col) {
                    if (_map[row][col] == 'c') {
                        _coins[std::array<std::size_t, 2>{col, row}] = std::make_unique<Coin>(
                            std::array<float, 2>{static_cast<float>(col * RATIO), static_cast<float>(row * RATIO)});
                    } else if (_map[row][col] == 'e') {
                        _traps[std::array<std::size_t, 2>{col, row}] = std::make_unique<Trap>(
                            std::array<float, 2>{static_cast<float>(col * RATIO), static_cast<float>(row * RATIO)},
                            _zapper_sprite, _zappedSound, Player::PlayerState::ZAPPED);
                    } else if (_map[row][col] == 'l') {
                        _traps[std::array<std::size_t, 2>{col, row}] = std::make_unique<Trap>(
                            std::array<float, 2>{static_cast<float>(col * RATIO), static_cast<float>(row * RATIO)},
                            _laser_sprite, _firedSound, Player::PlayerState::FIRED);
                    } else if (_map[row][col] == 'm') {
                        _traps[std::array<std::size_t, 2>{col, row}] = std::make_unique<Trap>(
                            std::array<float, 2>{static_cast<float>(col * RATIO), static_cast<float>(row * RATIO)},
                            _missile_sprite, _firedSound, Player::PlayerState::FIRED);
                    }
                }
            }
			DEBUG << "MAP: " << message;
		} catch (const std::exception &e) {
			ERROR << "map: Invalid argument.";
		}
	}
}
