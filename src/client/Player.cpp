/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Player.cpp
*/
/**
 * @file Player.cpp
 * @brief The Player.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "client/Player.hpp"

namespace Jetpack {
    /**
     * @brief Constructor for Player class
     * @param id The ID of the player
     * @param textureSize The size of the texture
     */
    Player::Player(std::size_t id, sf::Vector2u textureSize) :
		_id(id), _animation(textureSize)
    {
        DEBUG << "Player created: " << id;
		_animation.addAnimation("normal", 4, {textureSize.x / 4, textureSize.y / 4}, {0, 0}, 8.0f, true);
		_animation.addAnimation("jetpack", 4, {textureSize.x / 4, textureSize.y / 4}, {0, textureSize.x / 4}, 8.0f, true);
		_animation.addAnimation("zapped", 4, {textureSize.x / 4, textureSize.y / 4}, {0, 2 * (textureSize.x / 4)}, 8.0f, false);
        _animation.addAnimation("fired", 4, {textureSize.x / 4, textureSize.y / 4}, {0, 3 * (textureSize.x / 4)}, 8.0f, false);
		_animation.setCurrentAnimation("normal");
		_animation.play();
    }

    /**
     * @brief Destructor for Player class
     */
    Player::~Player()
    {
        DEBUG << "Player destroyed: " << _id;
    }

    /**
     * @brief Gets the ID of the player
     * @return The ID of the player
     */
    const std::size_t &Player::getId() const
    {
        return _id;
    }

    /**
     * @brief Gets the pseudo of the player
     * @return The pseudo of the player
     */
    const std::string &Player::getPseudo() const
    {
        return _pseudo;
    }

    /**
     * @brief Sets the pseudo of the player
     * @param pseudo The pseudo of the player
     */
    void Player::setPseudo(const std::string &pseudo)
    {
        _pseudo = pseudo;
    }

    /**
     * @brief Gets the alive status of the player
     * @return The alive status of the player
     */
    const bool &Player::isAlive() const
    {
        return _alive;
    }

    /**
     * @brief Sets the alive status of the player
     * @param alive The alive status of the player
     */
    void Player::setAlive(bool alive)
    {
        _alive = alive;
    }

    /**
     * @brief Gets the visible status of the player
     * @return The visible status of the player
     */
    const bool &Player::isVisible() const
    {
        return _visible;
    }

    /**
     * @brief Sets the visible status of the player
     * @param visible The visible status of the player
     */
    void Player::setVisible(bool visible)
    {
        _visible = visible;
    }

    /**
     * @brief Gets the score of the player
     * @return The score of the player
     */
    const std::size_t &Player::getScore() const
    {
        return _score;
    }

    /**
     * @brief Sets the score of the player
     * @param score The score of the player
     */
    void Player::setScore(std::size_t score)
    {
        _score = score;
    }

    /**
     * @brief Gets the position of the player
     * @return The position of the player
     */
    const std::array<float, 2> &Player::getPosition() const
    {
        return _position;
    }

    /**
     * @brief Sets the position of the player
     * @param position The position of the player
     */
    void Player::setPosition(const std::array<float, 2> &position)
    {
        _position = position;
    }

    /**
     * @brief Gets the animation of the player
     * @return The animation of the player
     */
	Animation &Player::getAnimation()
	{
		return _animation;
	}

    /**
     * @brief Gets the state of the player
     * @return The state of the player
     */
	const Player::PlayerState &Player::getPlayerState() const
	{
		return _player_state;
	}

    /**
     * @brief Sets the state of the player
     * @param playerState The state of the player
     */
	void Player::setPlayerState(PlayerState playerState)
	{
		_player_state = playerState;
		if (_player_state == PlayerState::NORMAL) {
			_animation.setCurrentAnimation("normal");
		} else if (_player_state == PlayerState::JETPACK) {
			_animation.setCurrentAnimation("jetpack");
		} else if (_player_state == PlayerState::ZAPPED) {
			_animation.setCurrentAnimation("zapped");
		} else if (_player_state == PlayerState::FIRED) {
            _animation.setCurrentAnimation("fired");
        }
	}
}