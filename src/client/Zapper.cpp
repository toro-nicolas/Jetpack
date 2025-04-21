/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Zapper.cpp
*/
/**
 * @file Zapper.cpp
 * @brief The Zapper.cpp
 * @author Nicolas TORO
 */

#include "client/Zapper.hpp"

namespace Jetpack {
    /**
     * @brief Constructor for Zapper class
     * @param position The position of the Zapper
     */
    Zapper::Zapper(std::array<float, 2> position)
        : _position(position)
    {
        DEBUG << "Zapper created";
    }

    /**
     * @brief Destructor for Zapper class
     */
    Zapper::~Zapper()
    {
        DEBUG << "Zapper destroyed";
    }

    /**
     * @brief Get the position of the Zapper
     * @return The position of the Zapper
     */
    const std::array<float, 2> &Zapper::getPosition() const
    {
        return _position;
    }
}