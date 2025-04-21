/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Cwd.cpp
*/
/**
 * @file Cwd.cpp
 * @brief The Cwd.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "utils/Cwd.hpp"

namespace Jetpack {
    Cwd::Cwd()
    {
        char *tmp = nullptr;

        DEBUG << "Cwd creation";
        tmp = getcwd(nullptr, 0);
        if (tmp == nullptr)
            throw JetpackError(
                "Getcwd failed: " + std::string(strerror(errno)));
        _pwd = tmp;
        free(tmp);
    }

    Cwd::~Cwd()
    {
        DEBUG << "Cwd destruction";
    }

    std::string Cwd::getPwd() const
    {
        return _pwd;
    }
}