/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Player.cpp
*/
/**
 * @file Player.cpp
 * @brief The Player.cpp
 * @author Nicolas TORO
 */

#include "client/Player.hpp"

namespace Jetpack {
    Player::Player(std::size_t id, sf::Vector2u textureSize) :
		_id(id), _animation(textureSize)
    {
        DEBUG << "Player created: " << id;
		_animation.addAnimation("normal", 4, {textureSize.x / 4, textureSize.y / 3}, {0, 0}, 8.0f, true);
		_animation.addAnimation("jetpack", 4, {textureSize.x / 4, textureSize.y / 3}, {0, textureSize.x / 4}, 8.0f, true);
		_animation.addAnimation("zapped", 4, {textureSize.x / 4, textureSize.y / 3}, {0, 2 * (textureSize.x / 4)}, 8.0f, true);
		_animation.setCurrentAnimation("normal");
		_animation.play();
    }

    const std::size_t &Player::getId() const
    {
        return _id;
    }

    const std::string &Player::getPseudo() const
    {
        return _pseudo;
    }

    void Player::setPseudo(const std::string &pseudo)
    {
        _pseudo = pseudo;
    }

    const bool &Player::isAlive() const
    {
        return _alive;
    }

    void Player::setAlive(bool alive)
    {
        _alive = alive;
    }

    const std::size_t &Player::getScore() const
    {
        return _score;
    }

    void Player::setScore(std::size_t score)
    {
        _score = score;
    }

    const std::array<float, 2> &Player::getPosition() const
    {
        return _position;
    }

    void Player::setPosition(const std::array<float, 2> &position)
    {
        _position = position;
    }

	Animation &Player::getAnimation()
	{
		return _animation;
	}

	const Player::PlayerState &Player::getPlayerState() const
	{
		return _player_state;
	}

	void Player::setPlayerState(PlayerState playerState)
	{
		_player_state = playerState;
		if (_player_state == PlayerState::NORMAL) {
			_animation.setCurrentAnimation("normal");
		} else if (_player_state == PlayerState::JETPACK) {
			_animation.setCurrentAnimation("jetpack");
		} else if (_player_state == PlayerState::ZAPPED) {
			_animation.setCurrentAnimation("zapped");
		}
	}
}