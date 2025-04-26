/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Exception.hpp
*/
/**
 * @file Exception.hpp
 * @brief The Exception.hpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#ifndef EXCEPTION_HPP_
	#define EXCEPTION_HPP_

    #include "Logs.hpp"

namespace Jetpack {
    /**
     * @class JetpackUsage
     * @brief An exception class for usage errors
     */
    class JetpackUsage : public std::exception {
        public:
            /**
             * @brief Constructor for JetpackUsage class
             */
            explicit JetpackUsage() {}
            /**
             * @brief Destructor for JetpackUsage class
             */
            ~JetpackUsage() override = default;
    };



    /**
     * @class JetpackStop
     * @brief An exception class for stopping the Jetpack
     */
    class JetpackStop : public std::exception {
        public:
            /**
             * @brief Constructor for JetpackStop class
             * @param message The message of the what() function
             */
            explicit JetpackStop(const std::string &message) : _message(message) {}
            /**
             * @brief Destructor for JetpackStop class
             */
            ~JetpackStop() override = default;



            /**
             * @brief Gets the message of the exception
             * @return The message of the exception
             */
            const char *what() const noexcept override { return _message.c_str(); }

        private:
            std::string _message; /* Message of the exception */
    };



    /**
     * @class JetpackError
     * @brief An exception class for Jetpack errors
     */
	class JetpackError : public std::exception {
		public:
            /**
             * @brief Constructor for JetpackError class
             * @param message The message of the what() function
             */
			explicit JetpackError(const std::string &message) : _message(message) {}
            /**
             * @brief Destructor for JetpackError class
             */
			~JetpackError() override = default;



            /**
             * @brief Gets the message of the exception
             * @return The message of the exception
             */
			const char *what() const noexcept override { return _message.c_str(); }

		private:
			std::string _message; /* Message of the exception */
	};
}

#endif /* EXCEPTION_HPP_ */
