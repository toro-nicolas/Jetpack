/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Logs.hpp
*/
/**
 * @file Logs.hpp
 * @brief The Logs.hpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#ifndef LOGS_HPP_
	#define LOGS_HPP_

    #include <exception>
    #include <string>
    #include <algorithm>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <poll.h>
    #include <filesystem>
    #include <cstdlib>
    #include <cstring>
    #include <vector>
    #include <unordered_map>
    #include <functional>
    #include <csignal>
    #include <fstream>
    #include <pwd.h>
	#include <cmath>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <iomanip>
    #include <iostream>
    #include <unordered_set>
    #include <map>
    #include <thread>
    #include <queue>
    #include <mutex>
    #include <string_view>

    #define    RESET "\033[0m"
    #define    BLACK "\033[0;30m"
    #define    RED "\033[0;31m"
    #define    GREEN "\033[0;32m"
    #define    YELLOW "\033[0;33m"
    #define    BLUE "\033[0;34m"
    #define    MAGENTA "\033[0;35m"
    #define    CYAN "\033[0;36m"
    #define    WHITE "\033[0;37m"
    #define    LIGHT_GREY "\033[0;37m"
    #define    DARK_GREY "\033[0;90m"
    #define    BOLD "\033[1m"
    #define    ITALIC "\033[3m"
    #define    UNDERLINE "\033[4m"
    #define    BLINK "\033[5m"
    #define    REVERSE "\033[7m"
    #define    HIDDEN "\033[8m"

    #define UNUSED __attribute__((unused))

namespace Jetpack::Logs {
    /**
     * @class Time
     * @brief A class that represents the time
     * @details This class is used to get the local time
     */
    class Time {
        public:
            /**
             * @brief Gets the local time
             * @return <b>std::string</b> The local time
             */
            static std::string getLocalTime();
    };



    extern bool debug_mode; /* Debug mode */



    /**
     * @class Debug
     * @brief A class for debugging
     * @details This class is used to print debug messages
     */
    class Debug {
        public:
            /**
             * @brief Constructor of the Debug
             * @param file The file that contains the debug
             * @param line The line that contains the debug
             * @param func The function that contains the debug
             */
            Debug(const std::string file = "", const int line = 0, const std::string func = "");
            /**
             * @brief Destructor of the Debug
             */
            ~Debug();



            /**
             * @brief Print a debug point
             * @param file The file that contains the debug point
             * @param line The line that contains the debug point
             * @param func The function that contains the debug point
             */
            static void point(const std::string file, const int line, const std::string func);



            /**
             * @brief Print a debug message
             * @param message The message to print
             * @return <b>Debug &</b> The debug object
             */
            template <typename T>
            Debug& operator<<(const T& message) {
                if (!debug_mode)
                    return *this;
                std::cout << message;
                return *this;
            }
            /**
             * @brief Print a debug message
             * @param pf The message to print
             * @return <b>Debug &</b> The debug object
             */
            Debug& operator<<(std::ostream& (*pf)(std::ostream&));
    };



    /**
     * @class Error
     * @brief A class for errors
     * @details This class is used to print error messages
     */
    class Error {
        public:
            /**
             * @brief Constructor of the Error
             * @param file The file that contains the error
             * @param line The line that contains the error
             * @param func The function that contains the error
             */
            Error(const std::string file = "", const int line = 0, const std::string func = "");
            /**
             * @brief Destructor of the Error
             */
            ~Error();



            /**
             * @brief Print an error message
             * @param message The message to print
             * @return <b>Error &</b> The error object
             */
            template <typename T>
            Error& operator<<(const T& message) {
                std::cerr << message;
                return *this;
            }
            /**
             * @brief Print an error message
             * @param pf The message to print
             * @return <b>Error &</b> The error object
             */
            Error& operator<<(std::ostream& (*pf)(std::ostream&));
    };



    /**
     * @class Warning
     * @brief A class for warnings
     * @details This class is used to print warning messages
     */
    class Warning {
        public:
            /**
             * @brief Constructor of the Warning
             * @param file The file that contains the warning
             * @param line The line that contains the warning
             * @param func The function that contains the warning
             */
            Warning(const std::string file = "", const int line = 0, const std::string func = "");
            /**
             * @brief Destructor of the Warning
             */
            ~Warning();



            /**
             * @brief Print a warning message
             * @param message The message to print
             * @return <b>Warning &</b> The warning object
             */
            template <typename T>
            Warning& operator<<(const T& message) {
                if (!debug_mode)
                    return *this;
                std::cerr << message;
                return *this;
            }
            /**
             * @brief Print a warning message
             * @param pf The message to print
             * @return <b>Warning &</b> The warning object
             */
            Warning& operator<<(std::ostream& (*pf)(std::ostream&));
    };



    /* Logs macros */

    #define DEBUG Jetpack::Logs::Debug(__FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define DEBUG_CONCAT Jetpack::Logs::Debug()
    #define POINT Jetpack::Logs::Debug::point(__FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define ERROR Jetpack::Logs::Error(__FILE__, __LINE__, __PRETTY_FUNCTION__)
    #define WARNING Jetpack::Logs::Warning(__FILE__, __LINE__, __PRETTY_FUNCTION__)
}

#endif /* LOGS_HPP_ */
