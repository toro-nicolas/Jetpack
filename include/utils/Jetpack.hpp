/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Jetpack.hpp
*/
/**
 * @file Jetpack.hpp
 * @brief The Jetpack.hpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#ifndef FTP_HPP_
	#define FTP_HPP_

	#define UNUSED __attribute__((unused))
	#define ENDL "\n"
	#define MAX_CLIENTS 100
	#define MAX_RESPONSE_SIZE 1024

    #include "utils/Socket.hpp"
    #include "utils/Cwd.hpp"

namespace Jetpack {
    #define TRAP_LIST "elm"

    /* Threads */

    //#define UPDATE_VAR(mutex) std::lock_guard<std::mutex> lock(mutex);
    // Manual lock and unlock
    //std::unique_lock<std::mutex> lock(mutex);
    //lock.unlock();



    /* Protocol */

	#define CODE_OK 200
	#define CODE_ERROR 500

    enum CmdCode {
        CODE_GAME = 1,
        CODE_CLIENTS = 2,
        CODE_PERSONNAL = 3,
    };

	enum CmdID {
        CMD_ID_NOT_FOUND = -1,
		CMD_ID_ID = 0,
		CMD_MAP_ID = 1,
		CMD_PSEUDO_ID = 2,
		CMD_MOVE_ID = 3,
		CMD_CLIENTS_NB_ID = 4,
		CMD_CLIENTS_STATS_ID = 5,
		CMD_CLIENTS_POSITIONS_ID = 6,
	};

    const std::array<std::string, 7> CMD_ID_STR = {
        "ID",
        "MAP",
        "PSEUDO",
        "MOVE",
        "CLIENTS_NB",
        "CLIENTS_STATS",
        "CLIENTS_POSITIONS"
    };



    /* Global functions */

    /**
     * @brief Closes the jetpack client
     * @note This function is a signal handler for SIGINT
     * @param signal The signal to handle
     * @throw JetpackStop if the jetpack is closed
     */
	void closeJetpack(int signal);

    /**
     * @brief Converts a string to a vector of strings
     * @param str The string to convert
     * @param delimiters The delimiters to use
     * @return A vector of strings
     */
	std::vector<std::string> stringToVector(std::string str, std::string delimiters);
}

#endif /* FTP_HPP_ */
