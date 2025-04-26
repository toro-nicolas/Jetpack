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
    /**
     * @class Cwd
     * @brief An encapsulation of the current working directory (CWD)
     */
    class Cwd
    {
        public:
            /**
             * @brief Constructor for Cwd class
             * @note This constructor gets the current working directory
             * @throw JetpackError if getcwd fails
             */
            Cwd();
            /**
             * @brief Deleted copy constructor
             */
            ~Cwd();



            /**
             * @brief Gets the current working directory
             * @return The current working directory
             */
            std::string getPwd() const;

        private:
            std::string _pwd; /* Current working directory */
    };
}

#endif /* CWD_HPP_ */
