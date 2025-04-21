/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Coin.hpp
*/
/**
 * @file Coin.hpp
 * @brief The Coin.hpp
 * @author Nicolas TORO
 */

#ifndef COIN_HPP_
    #define COIN_HPP_

    #include "utils/Jetpack.hpp"

namespace Jetpack {
    class Coin
    {
        public:
            /**
             * @brief Constructor for Coin class
             * @param position The position of the coin
             */
            Coin(std::array<float, 2> position = {0, 0});

            /**
             * @brief Destructor for Coin class
             */
            ~Coin();



            /**
             * @brief Get the position of the coin
             * @return The position of the coin
             */
            const std::array<float, 2> &getPosition() const;

            /**
             * @brief Get the collected status of the coin
             * @return The collected status of the coin
             */
            const bool &isCollected() const;

            /**
             * @brief Set the collected status of the coin
             * @param collected The collected status of the coin
             */
            void setCollected(bool collected);

        private:
            std::array<float, 2> _position; /* Position of the coin */
            bool _collected = false; /* If the coin is collected or not */
    };
}

#endif /* COIN_HPP_ */
