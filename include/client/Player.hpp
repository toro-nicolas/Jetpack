/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Player.hpp
*/
/**
 * @file Player.hpp
 * @brief The Player.hpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include "client/Animation.hpp"

namespace Jetpack {
    /**
     * @class Player
     * @brief A class that represents a player in the game
     */
    class Player
    {
        public:
            /* Constructor and destructor */

            /**
             * @brief Constructor for Player class
             * @param id The ID of the player
             * @param textureSize The size of the texture
             */
            Player(std::size_t id, sf::Vector2u textureSize);
            /**
             * @brief Destructor for Player class
             */
            ~Player();
            /**
             * @brief Deleted copy constructor
             * @param other The Player object to copy from
             */
            Player(const Player &) = delete;
            /**
             * @brief Deleted assignment operator
             * @param other The Player object to assign from
             * @return Reference to the current object
             */
            Player &operator=(const Player &) = delete;



            /* The state of the player */
			enum class PlayerState {
				NORMAL,
				JETPACK,
				ZAPPED,
                FIRED
			};



            /* Getter and Setter for player information */

            /**
             * @brief Gets the ID of the player
             * @return The ID of the player
             */
            const std::size_t &getId() const;
            /**
             * @brief Gets the pseudo of the player
             * @return The pseudo of the player
             */
            const std::string &getPseudo() const;
            /**
             * @brief Sets the pseudo of the player
             * @param pseudo The pseudo of the player
             */
            void setPseudo(const std::string &pseudo);
            /**
             * @brief Gets the alive status of the player
             * @return The alive status of the player
             */
            const bool &isAlive() const;
            /**
             * @brief Sets the alive status of the player
             * @param alive The alive status of the player
             */
            void setAlive(bool alive);
            /**
             * @brief Gets the visible status of the player
             * @return The visible status of the player
             */
            const bool &isVisible() const;
            /**
             * @brief Sets the visible status of the player
             * @param visible The visible status of the player
             */
            void setVisible(bool visible);
            /**
             * @brief Gets the score of the player
             * @return The score of the player
             */
            const std::size_t &getScore() const;
            /**
             * @brief Sets the score of the player
             * @param score The score of the player
             */
            void setScore(std::size_t score);
            /**
             * @brief Gets the position of the player
             * @return The position of the player
             */
            const std::array<float, 2> &getPosition() const;
            /**
             * @brief Sets the position of the player
             * @param position The position of the player
             */
            void setPosition(const std::array<float, 2> &position);
            /**
             * @brief Gets the animation of the player
             * @return The animation of the player
             */
			Animation &getAnimation();
            /**
             * @brief Gets the state of the player
             * @return The state of the player
             */
			const PlayerState &getPlayerState() const;
            /**
             * @brief Sets the state of the player
             * @note This function changes the animation of the player
             * @param playerState The state of the player
             */
			void setPlayerState(PlayerState playerState);



        private:
            std::size_t _id; /* The ID of the player */
            std::string _pseudo; /* The pseudo of the player */
            bool _alive = true; /* The alive status of the player */
            bool _visible = true; /* The visible status of the player */
            std::size_t _score = 0; /* The score of the player */
            std::array<float, 2> _position = {0, 0}; /* The position of the player */
			Animation _animation; /* The animation of the player */
			PlayerState _player_state = PlayerState::NORMAL; /* The state of the player */
    };
}

#endif /* PLAYER_HPP_ */
