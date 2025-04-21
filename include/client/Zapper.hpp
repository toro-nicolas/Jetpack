/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Zapper.hpp
*/
/**
 * @file Zapper.hpp
 * @brief The Zapper.hpp
 * @author Nicolas TORO
 */

#ifndef ZAPPER_HPP_
    #define ZAPPER_HPP_

    #include "utils/Jetpack.hpp"

namespace Jetpack {
    class Zapper
    {
        public:
            /**
             * @brief Constructor for Zapper class
             * @param position The position of the Zapper
             */
            Zapper(std::array<float, 2> position = {0, 0});

            /**
             * @brief Destructor for Zapper class
             */
            ~Zapper();



            /**
             * @brief Get the position of the Zapper
             * @return The position of the Zapper
             */
            const std::array<float, 2> &getPosition() const;

        private:
            std::array<float, 2> _position; /* Position of the Zapper */
    };
}


#endif /* ZAPPER_HPP_ */
