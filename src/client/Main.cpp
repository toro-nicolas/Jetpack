/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The main.cpp
*/
/**
 * @file main.cpp
 * @brief The main.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "client/Client.hpp"

/**
 * @brief Display the help message
 */
void display_help()
{
    std::cout << "USAGE: ./jetpack_client -h <ip> -p <port> [-d]" << std::endl << std::endl
        << "DESCRIPTION:" << std::endl
        << "\t-h <ip>\tThe server IP address" << std::endl
        << "\t-p <port>\tThe port number on which the server socket listens" << std::endl
        << "\t-d\t\tEnable debug mode" << std::endl
        << "\t--help\t\tDisplay this help message" << std::endl << std::endl
        << "CREDITS:" << std::endl
        << "\tMade by Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO" << std::endl
        << "\tEPITECH Nice 2025" << std::endl;
}

/**
 * @brief Main function
 * @param ac The number of arguments
 * @param av The arguments
 * @return 0 on success, 84 on failure
 */
int main(int ac, char **av)
{
	try {
		std::signal(SIGINT, Jetpack::Client::closeJetpackClient);
		std::signal(SIGPIPE, SIG_IGN);
		Jetpack::Client client(ac, av);
		client.run();
	} catch (const Jetpack::JetpackUsage &e) {
		display_help();
		return 84;
	} catch (const Jetpack::JetpackStop &e) {
		std::cout << e.what() << std::endl;
		return 0;
	} catch (const std::exception &e) {
		ERROR << "EXCEPTION: " << e.what();
		return 84;
	}
	return 0;
}