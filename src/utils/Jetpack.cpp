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

	void closeJetpack(UNUSED int signal)
	{
        DEBUG << "Close jetpack";
		throw JetpackStop("Jetpack closed");
	}
}