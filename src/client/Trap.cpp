/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Trap.cpp
*/
/**
 * @file Trap.cpp
 * @brief The Trap.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "client/Trap.hpp"

namespace Jetpack {
    /**
     * @brief Constructor for Trap class
     * @param position The position of the Trap
     * @param sprite The sprite of the Trap
     * @param sound The sound of the Trap
     * @param player_state The state of the player after being hit by the Trap
     */
    Trap::Trap(std::array<float, 2> position,
        sf::Sprite &sprite, sf::Sound &sound,
        Player::PlayerState player_state) :
        _position(position), _sprite(sprite), _sound(sound),
        _player_state(player_state)
    {
        DEBUG << "Trap created";
    }

    /**
     * @brief Destructor for Trap class
     */
    Trap::~Trap()
    {
        DEBUG << "Trap destroyed";
    }

    /**
     * @brief Gets the position of the Trap
     * @return The position of the Trap
     */
    const std::array<float, 2> &Trap::getPosition() const
    {
        return _position;
    }

    /**
     * @brief Gets the sprite of the Trap
     * @return The sprite of the Trap
     */
    sf::Sprite &Trap::getSprite()
    {
        return _sprite;
    }

    /**
     * @brief Gets the sound of the Trap
     * @return The sound of the Trap
     */
    sf::Sound &Trap::getSound()
    {
        return _sound;
    }

    /**
     * @brief Gets the state of the player after being hit by the Trap
     * @return The state of the player after being hit by the Trap
     */
    const Player::PlayerState &Trap::getPlayerState() const
    {
        return _player_state;
    }
}