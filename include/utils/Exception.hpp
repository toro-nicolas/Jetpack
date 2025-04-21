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
    class JetpackUsage : public std::exception {
        public:
            explicit JetpackUsage() {}
            ~JetpackUsage() override = default;
    };



    class JetpackStop : public std::exception {
        public:
            explicit JetpackStop(const std::string &message) : _message(message) {}
            ~JetpackStop() override = default;

            const char *what() const noexcept override { return _message.c_str(); }

        private:
            std::string _message;
    };



	class JetpackError : public std::exception {
		public:
			explicit JetpackError(const std::string &message) : _message(message) {}
			~JetpackError() override = default;

			const char *what() const noexcept override { return _message.c_str(); }

		private:
			std::string _message;
	};
}

#endif /* EXCEPTION_HPP_ */
