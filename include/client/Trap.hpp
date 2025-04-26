/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Trap.hpp
*/
/**
 * @file Trap.hpp
 * @brief The Trap.hpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#ifndef ZAPPER_HPP_
    #define ZAPPER_HPP_

    #include "client/Player.hpp"

namespace Jetpack {
    /**
     * @class Trap
     * @brief A class that represents a zapper in the game
     */
    class Trap
    {
        public:
            /* Constructor and destructor */

            /**
             * @brief Constructor for Trap class
             * @param position The position of the Trap
             * @param sprite The sprite of the Trap
             * @param sound The sound of the Trap
             * @param player_state The state of the player after being hit by the Trap
             */
            Trap(std::array<float, 2> position,
                sf::Sprite &sprite, sf::Sound &sound,
                Player::PlayerState player_state = Player::PlayerState::NORMAL);
            /**
             * @brief Destructor for Trap class
             */
            ~Trap();



            /* Getter and Setter for Trap information */

            /**
             * @brief Gets the position of the Trap
             * @return The position of the Trap
             */
            const std::array<float, 2> &getPosition() const;
            /**
             * @brief Gets the sprite of the Trap
             * @return The sprite of the Trap
             */
            sf::Sprite &getSprite();
            /**
             * @brief Gets the sound of the Trap
             * @return The sound of the Trap
             */
            sf::Sound &getSound();
            /**
             * @brief Gets the state of the player after being hit by the Trap
             * @return The state of the player after being hit by the Trap
             */
            const Player::PlayerState &getPlayerState() const;



        private:
            std::array<float, 2> _position; /* Position of the Trap */
            sf::Sprite &_sprite; /* Sprite of the Trap */
            sf::Sound &_sound; /* Sound of the Trap */
            Player::PlayerState _player_state; /* State of the player after being hit by the Trap */
    };
}


#endif /* ZAPPER_HPP_ */
