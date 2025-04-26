/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Animation.hpp
*/

#ifndef ANIMATION_HPP_
    #define ANIMATION_HPP_

    #include "utils/Jetpack.hpp"
	#include <SFML/Audio/Music.hpp>
	#include <SFML/Graphics/RectangleShape.hpp>
	#include <SFML/Graphics/Texture.hpp>
	#include <SFML/Graphics.hpp>
	#include <SFML/Audio/Sound.hpp>
	#include <SFML/Graphics/Sprite.hpp>
	#include <SFML/System/Vector2.hpp>
	#include <SFML/Window/Keyboard.hpp>
	#include <SFML/Audio.hpp>

namespace Jetpack {
    /**
     * @class Animation
     * @brief A class that handles sprite animations
     */
    class Animation {
        public:
            /* Constructor and destructor */

            /**
             * @brief Constructor for Animation class
             * @param textureSize Size of the texture (default is {0, 0})
             */
            Animation(sf::Vector2u textureSize = {0, 0});
            /**
             * @brief Destructor for Animation class
             */
            ~Animation();



            /* The animation functions */

			/**
			 * @brief Sets the texture size for the animation
			 * @param textureSize Size of the texture
			 */
			void setTextureSize(sf::Vector2u textureSize);
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
            bool addAnimation(const std::string& name, int frameCount, sf::Vector2u frameSize, sf::Vector2u startPosition,float fps = 12.0f, bool loop = true);
            /**
             * @brief Sets the current animation
             * @param name Name of the animation to set
             * @param resetFrame Whether to start the animation from the beginning (default is true)
             * @return True if the animation was set successfully
             * and false otherwise
             */
            bool setCurrentAnimation(const std::string& name, bool resetFrame = true);
            /**
             * @brief Updates the animation based on elapsed time
             * @param deltaTime Elapsed time since last update
             */
            void update(float deltaTime);
            /**
             * @brief Plays the current animation
             */
            void play();
            /**
             * @brief Pauses the current animation
             */
            void pause();
            /**
             * @brief Stops the current animation and resets it
             */
            void stop();
            /**
             * @brief Checks if the animation is playing
             * @return True if the animation is playing
             */
            bool isPlaying() const;
            /**
             * @brief Gets the current animation name
             * @return Name of the current animation
             */
            std::string getCurrentAnimationName() const;
            /**
             * @brief Sets whether the sprite should be flipped horizontally
             * @param flip True to flip the sprite horizontally
             */
            void setFlipX(bool flip);
            /**
             * @brief Sets whether the sprite should be flipped vertically
             * @param flip True to flip the sprite vertically
             */
            void setFlipY(bool flip);
			/**
			 * @brief Gets the texture rectangle for the current frame
			 * @return The texture rectangle for the current frame
			 */
			const sf::IntRect& getTextureRect() const;

		private:
            /**
             * @brief Structure to store animation data
             */
            struct AnimationData {
                std::string name; /* Name of the animation */
                int frameCount; /* Number of frames in the animation */
                sf::Vector2u frameSize; /* Size of each frame */
                sf::Vector2u startPosition; /* Starting position of the animation in the sprite sheet */
                float frameDuration; /* Duration of each frame in seconds */
                bool loop; /* Whether the animation should loop */
            };
            /**
             * @brief Updates the texture rectangle for the current frame
             * @return The updated texture rectangle
             */
            void updateTextureRect();



		private:
			sf::IntRect _textureRect; /* The texture rectangle for the current frame */
			sf::Vector2u _textureSize; /* Size of the texture */
            std::unordered_map<std::string, AnimationData> _animations; /* Map of animations (name, AnimationData) */
            std::string _currentAnimationName; /* Name of the current animation */
            int _currentFrame; /* Current frame index */
            float _timeAccumulator; /* Time accumulator for frame duration */
            bool _isPlaying; /* The playing status of the animation */
            bool _flipX; /* The flip status of the animation on the X axis */
            bool _flipY; /* The flip status of the animation on the Y axis */
    };
}

#endif /* ANIMATION_HPP_ */
