/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The PositionHash.hpp
*/
/**
 * @file PositionHash.hpp
 * @brief The PositionHash.hpp
 * @author Nicolas TORO
 */

#ifndef POSITIONHASH_HPP_
    #define POSITIONHASH_HPP_

    #include "utils/Logs.hpp"

namespace Jetpack {
    /**
     * @class PositionHash
     * @brief A class that represents a hash function for positions
     */
    class PositionHash
    {
        public:
            /**
             * @brief Hash function for a 2D position
             * @param pos The position to hash
             * @return The hash value of the position
             */
            std::size_t operator()(const std::array<std::size_t, 2> &pos) const noexcept;



        private:
            /**
             * @brief Hash combine function
             * @param seed The seed value
             * @param value The value to hash
             */
            template<typename T>
            static void hash_combine(std::size_t &seed, const T &value) noexcept;
    };
}

#endif /* POSITIONHASH_HPP_ */
