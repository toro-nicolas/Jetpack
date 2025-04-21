/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Map.cpp
*/
/**
 * @file Map.cpp
 * @brief The Map.cpp
 * @author Nicolas TORO
 */

#include "client/Client.hpp"
#include <memory>

namespace Jetpack {
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
            _zappers.clear();
            for (std::size_t row = 0; row < _map.size(); ++row) {
                for (std::size_t col = 0; col < _map[row].size(); ++col) {
                    if (_map[row][col] == 'c') {
                        _coins.push_back(std::make_unique<Coin>(std::array<float, 2>{static_cast<float>(col * RATIO), static_cast<float>(row * RATIO)}));
                    } else if (_map[row][col] == 'e') {
                        _zappers.push_back(std::make_unique<Zapper>(std::array<float, 2>{static_cast<float>(col * RATIO), static_cast<float>(row * RATIO)}));
                    }
                }
            }
			DEBUG << "MAP: " << message;
		} catch (const std::exception &e) {
			ERROR << "map: Invalid argument.";
		}
	}
}
