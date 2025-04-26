/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Jetpack.cpp
*/
/**
 * @file Jetpack.cpp
 * @brief The Jetpack.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "utils/Jetpack.hpp"

namespace Jetpack {
    /**
     * @brief Converts a string to a vector of strings using the specified delimiters
     * @param str The string to convert
     * @param delimiters The delimiters to use for splitting the string
     * @return A vector of strings
     */
	std::vector<std::string> stringToVector(std::string str, std::string delimiters)
	{
		std::vector<std::string> array;
		size_t start = str.find_first_not_of(delimiters);

		while (start != std::string::npos) {
			size_t end = str.find_first_of(delimiters, start);
			if (end == std::string::npos)
				end = str.size();
			array.push_back(str.substr(start, end - start));
			start = str.find_first_not_of(delimiters, end);
		}
		return array;
	}

    /**
     * @brief Closes the jetpack
     * @note This function is a signal handler for SIGINT
     * @param signal The signal to handle
     * @throw JetpackStop if the jetpack is closed
     */
	void closeJetpack(UNUSED int signal)
	{
        DEBUG << "Close jetpack";
		throw JetpackStop("Jetpack closed");
	}
}