/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The PositionHash.cpp
*/
/**
 * @file PositionHash.cpp
 * @brief The PositionHash.cpp
 * @author Nicolas TORO
 */

#include "utils/PositionHash.hpp"

namespace Jetpack {
    /**
     * @brief Hash function for a 2D position
     * @param pos The position to hash
     * @return The hash value of the position
     */
    std::size_t PositionHash::operator()(const std::array<std::size_t, 2> &pos) const noexcept {
        std::size_t hash = 0;
        hash_combine(hash, pos[0]);
        hash_combine(hash, pos[1]);
        return hash;
    }

    /**
     * @brief Hash combine function
     * @param seed The seed value
     * @param value The value to hash
     */
    template<typename T>
    void PositionHash::hash_combine(std::size_t &seed, const T &value) noexcept {
        std::hash<T> hasher;
        seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
}