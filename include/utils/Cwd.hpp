/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Cwd.hpp
*/
/**
 * @file Cwd.hpp
 * @brief The Cwd.hpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#ifndef CWD_HPP_
    #define CWD_HPP_

    #include "utils/Exception.hpp"
    #include "utils/Logs.hpp"

namespace Jetpack {
    class Cwd
    {
        public:
            Cwd();
            ~Cwd();

            std::string getPwd() const;

        private:
            std::string _pwd;
    };
}

#endif /* CWD_HPP_ */
