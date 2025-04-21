/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Player.hpp
*/
/**
 * @file Player.hpp
 * @brief The Player.hpp
 * @author Nicolas TORO
 */

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include "client/Animation.hpp"

namespace Jetpack {
    class Player
    {
        public:
            Player(std::size_t id, sf::Vector2u textureSize);
            ~Player() = default;

            Player(const Player &) = delete;
            Player &operator=(const Player &) = delete;

			enum class PlayerState {
				NORMAL,
				JETPACK,
				ZAPPED
			};

            const std::size_t &getId() const;
            const std::string &getPseudo() const;
            void setPseudo(const std::string &pseudo);
            const bool &isAlive() const;
            void setAlive(bool alive);
            const std::size_t &getScore() const;
            void setScore(std::size_t score);
            const std::array<float, 2> &getPosition() const;
            void setPosition(const std::array<float, 2> &position);
			Animation &getAnimation();
			const PlayerState &getPlayerState() const;
			void setPlayerState(PlayerState playerState);

        protected:

        private:
            std::size_t _id;
            std::string _pseudo;
            bool _alive = true;
            std::size_t _score = 0;
            std::array<float, 2> _position = {0, 0};
			Animation _animation;
			PlayerState _player_state = PlayerState::NORMAL;
    };
}

#endif /* PLAYER_HPP_ */
