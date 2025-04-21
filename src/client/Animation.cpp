/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Animation.cpp
*/

#include "client/Animation.hpp"

namespace Jetpack {
	Animation::Animation(sf::Vector2u textureSize)
		: _textureSize(textureSize), _currentFrame(0), _timeAccumulator(0.0f),
		_isPlaying(false), _flipX(false), _flipY(false)
	{
		DEBUG << "Animation created";
	}

    Animation::~Animation()
    {
		DEBUG << "Animation destroyed";
    }

	void Animation::setTextureSize(sf::Vector2u textureSize)
	{
		_textureSize = textureSize;
	}

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

    void Animation::play()
    {
        _isPlaying = true;
    }

    void Animation::pause()
    {
        _isPlaying = false;
    }

    void Animation::stop()
    {
        _isPlaying = false;
        _currentFrame = 0;
        _timeAccumulator = 0.0f;
        updateTextureRect();
    }

    bool Animation::isPlaying() const
    {
        return _isPlaying;
    }

    std::string Animation::getCurrentAnimationName() const
    {
        return _currentAnimationName;
    }

    void Animation::setFlipX(bool flip)
    {
        if (_flipX != flip) {
            _flipX = flip;
            updateTextureRect();
        }
    }

    void Animation::setFlipY(bool flip)
    {
        if (_flipY != flip) {
            _flipY = flip;
            updateTextureRect();
        }
    }

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

	const sf::IntRect& Animation::getTextureRect() const
	{
		return _textureRect;
	}
}
