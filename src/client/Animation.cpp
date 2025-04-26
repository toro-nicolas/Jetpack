/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Animation.cpp
*/

#include "client/Animation.hpp"

namespace Jetpack {
    /**
     * @brief Constructor for Animation class
     * @param textureSize Size of the texture (default is {0, 0})
     */
	Animation::Animation(sf::Vector2u textureSize)
		: _textureSize(textureSize), _currentFrame(0), _timeAccumulator(0.0f),
		_isPlaying(false), _flipX(false), _flipY(false)
	{
		DEBUG << "Animation created";
	}

    /**
     * @brief Destructor for Animation class
     */
    Animation::~Animation()
    {
		DEBUG << "Animation destroyed";
    }

    /**
     * @brief Sets the texture size for the animation
     * @param textureSize Size of the texture
     */
	void Animation::setTextureSize(sf::Vector2u textureSize)
	{
		_textureSize = textureSize;
	}

    /**
     * @brief Adds an animation to the animation list
     * @param name Name of the animation
     * @param frameCount Number of frames in the animation
     * @param frameSize Size of each frame
     * @param startPosition Starting position of the animation in the sprite sheet
     * @param fps Frames per second for the animation (default is 12.0f)
     * @param loop Whether the animation should loop (default is true)
     * @return True if the animation was added successfully
     * and false otherwise
     */
    bool Animation::addAnimation(const std::string& name,
		int frameCount, sf::Vector2u frameSize,
        sf::Vector2u startPosition, float fps, bool loop)
    {
        if (name.empty() || frameCount <= 0 || frameSize.x <= 0 || frameSize.y <= 0 || fps <= 0)
            return false;

        AnimationData animation;
        animation.name = name;
        animation.frameCount = frameCount;
        animation.frameSize = frameSize;
        animation.startPosition = startPosition;
        animation.frameDuration = 1.0f / fps;
        animation.loop = loop;
        _animations[name] = animation;
        if (_currentAnimationName.empty())
            setCurrentAnimation(name);
        return true;
    }

    /**
     * @brief Sets the current animation
     * @param name Name of the animation to set
     * @param resetFrame Whether to start the animation from the beginning (default is true)
     * @return True if the animation was set successfully
     * and false otherwise
     */
    bool Animation::setCurrentAnimation(const std::string& name, bool resetFrame)
    {
        auto it = _animations.find(name);
        if (it == _animations.end())
            return false;

        if (_currentAnimationName == name && !resetFrame)
            return true;

        _currentAnimationName = name;

        if (resetFrame) {
            _currentFrame = 0;
            _timeAccumulator = 0.0f;
        }

        updateTextureRect();
        return true;
    }

    /**
     * @brief Updates the animation based on elapsed time
     * @param deltaTime Elapsed time since last update
     */
    void Animation::update(float deltaTime)
    {
        if (!_isPlaying || _currentAnimationName.empty())
            return;

        auto& animation = _animations[_currentAnimationName];

        _timeAccumulator += deltaTime;

        if (_timeAccumulator >= animation.frameDuration) {
            _timeAccumulator -= animation.frameDuration;
            _currentFrame++;
            if (_currentFrame >= animation.frameCount) {
                if (animation.loop) {
                    _currentFrame = 0;
                } else {
                    _currentFrame = animation.frameCount - 1;
                    _isPlaying = false;
                }
            }
            updateTextureRect();
        }
    }

    /**
     * @brief Plays the current animation
     */
    void Animation::play()
    {
        _isPlaying = true;
    }

    /**
     * @brief Pauses the current animation
     */
    void Animation::pause()
    {
        _isPlaying = false;
    }

    /**
     * @brief Stops the current animation
     */
    void Animation::stop()
    {
        _isPlaying = false;
        _currentFrame = 0;
        _timeAccumulator = 0.0f;
        updateTextureRect();
    }

    /**
     * @brief Checks if the animation is playing
     * @return True if the animation is playing
     */
    bool Animation::isPlaying() const
    {
        return _isPlaying;
    }

    /**
     * @brief Gets the current animation name
     * @return The current animation name
     */
    std::string Animation::getCurrentAnimationName() const
    {
        return _currentAnimationName;
    }

    /**
     * @brief Sets whether the sprite should be flipped horizontally
     * @param flip True to flip the sprite horizontally
     */
    void Animation::setFlipX(bool flip)
    {
        if (_flipX != flip) {
            _flipX = flip;
            updateTextureRect();
        }
    }

    /**
     * @brief Sets whether the sprite should be flipped vertically
     * @param flip True to flip the sprite vertically
     */
    void Animation::setFlipY(bool flip)
    {
        if (_flipY != flip) {
            _flipY = flip;
            updateTextureRect();
        }
    }

    /**
     * @brief Updates the texture rectangle for the current frame
     * @return The updated texture rectangle
     */
    void Animation::updateTextureRect()
    {
        int row = 0;
        int col = 0;
        int columns = 0;

        if (_currentAnimationName.empty())
            return;

        auto& animation = _animations[_currentAnimationName];

        row = animation.startPosition.y / animation.frameSize.y;
        col = animation.startPosition.x / animation.frameSize.x;

        columns = _textureSize.x / animation.frameSize.x;
        if (columns <= 0) columns = 1;

        row += _currentFrame / columns;
        col += _currentFrame % columns;

        sf::IntRect rect(
            col * animation.frameSize.x,
            row * animation.frameSize.y,
            animation.frameSize.x,
            animation.frameSize.y
        );

        if (_flipX) {
            rect.left += rect.width;
            rect.width = -rect.width;
        }

        if (_flipY) {
            rect.top += rect.height;
            rect.height = -rect.height;
        }
		_textureRect = rect;
    }

    /**
     * @brief Gets the texture rectangle for the current frame
     * @return The texture rectangle for the current frame
     */
	const sf::IntRect& Animation::getTextureRect() const
	{
		return _textureRect;
	}
}
