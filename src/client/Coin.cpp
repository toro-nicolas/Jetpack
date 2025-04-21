/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Coin.cpp
*/
/**
 * @file Coin.cpp
 * @brief The Coin.cpp
 * @author Nicolas TORO
 */

#include "client/Coin.hpp"

namespace Jetpack {
    /**
     * @brief Constructor for Coin class
     * @param position The position of the coin
     */
    Coin::Coin(std::array<float, 2> position)
        : _position(position)
    {
        DEBUG << "Coin created";
    }

    /**
     * @brief Destructor for Coin class
     */
    Coin::~Coin()
    {
        DEBUG << "Coin destroyed";
    }

    /**
     * @brief Get the position of the coin
     * @return The position of the coin
     */
    const std::array<float, 2> &Coin::getPosition() const
    {
        return _position;
    }

    /**
     * @brief Get the collected status of the coin
     * @return The collected status of the coin
     */
    const bool &Coin::isCollected() const
    {
        return _collected;
    }

    /**
     * @brief Set the collected status of the coin
     * @param collected The collected status of the coin
     */
    void Coin::setCollected(bool collected)
    {
        _collected = collected;
    }
}
