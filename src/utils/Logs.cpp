/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** The Logs.cpp
*/
/**
 * @file Logs.cpp
 * @brief The Logs.cpp
 * @author Christophe VANDEVOIR, Guillaume LECOCQ and Nicolas TORO
 */

#include "utils/Logs.hpp"

namespace Jetpack::Logs {
    bool debug_mode = false;
    
    /**
     * @brief Gets the local time
     * @return <b>std::string</b> The local time
     */
    std::string Time::getLocalTime()
    {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::ostringstream oss;

        oss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S")
            << "." << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }

    /**
     * @brief Constructor of the Debug
     * @param file The file that contains the debug
     * @param line The line that contains the debug
     * @param func The function that contains the debug
     */
    Debug::Debug(const std::string file, const int line,
        const std::string func)
    {
        if (!debug_mode)
            return;
        if (file.empty() && line == 0 && func.empty()) {
            std::cout << RESET YELLOW;
        } else {
            #ifdef DEBUG_MODE
                std::cout << RESET WHITE BOLD ITALIC
                    "[" << Time::getLocalTime() << "] " <<
                    "[FILE: " << file << ":" << line
                    << ", FUNCTION: " << func << "]: " RESET YELLOW << std::endl;
            #else
                std::cout << RESET YELLOW;
            #endif
        }
    }

    /**
     * @brief Destructor of the Debug
     */
    Debug::~Debug()
    {
        if (!debug_mode)
            return;
        std::cout << RESET << std::endl;
    }

    /**
     * @brief Print a debug point
     * @param file The file that contains the debug point
     * @param line The line that contains the debug point
     * @param func The function that contains the debug point
     */
    void Debug::point(UNUSED const std::string file, UNUSED const int line,
        UNUSED const std::string func)
    {
        if (!debug_mode)
            return;
        #ifdef DEBUG_MODE
            std::cout << RESET WHITE BOLD ITALIC
                "[" << Time::getLocalTime() << "] " <<
                "FILE: " << file << ":" << line <<
                RESET WHITE ", FUNCTION: " << func << RESET << std::endl;
        #endif
    }

    /**
     * @brief Print a debug message
     * @param pf The message to print
     * @return <b>Debug &</b> The debug object
     */
    Debug &Debug::operator<<(std::ostream &(*pf)(std::ostream &))
    {
        if (!debug_mode)
            return *this;
        std::cout << pf;
        return *this;
    }

    /**
     * @brief Constructor of the Error
     * @param file The file that contains the error
     * @param line The line that contains the error
     * @param func The function that contains the error
     */
    Error::Error(const std::string file, const int line,
        const std::string func)
    {
        if (file.empty() && line == 0 && func.empty())
            std::cerr << RESET RED;
        else
            std::cerr << RESET WHITE BOLD ITALIC
            "[" << Time::getLocalTime() << "] " <<
            "[FILE: " << file << ":" << line
            << ", FUNCTION: " << func << "]: "
            RESET RED;
        std::cerr << std::endl;
    }

    /**
     * @brief Destructor of the Error
     */
    Error::~Error()
    {
        std::cerr << RESET << std::endl;
    }

    /**
     * @brief Print an error message
     * @param pf The message to print
     * @return <b>Error &</b> The error object
     */
    Error &Error::operator<<(std::ostream &(*pf)(std::ostream &))
    {
        std::cerr << pf;
        return *this;
    }

    /**
     * @brief Constructor of the Warning
     * @param file The file that contains the warning
     * @param line The line that contains the warning
     * @param func The function that contains the warning
     */
    Warning::Warning(const std::string file, const int line,
        const std::string func)
    {
        if (!debug_mode)
            return;
        if (file.empty() && line == 0 && func.empty())
            std::cerr << RESET MAGENTA;
        else
            std::cerr << RESET WHITE BOLD ITALIC
            "[" << Time::getLocalTime() << "] " <<
            "[FILE: " << file << ":" << line
            << ", FUNCTION: " << func << "]: "
            RESET MAGENTA;
        std::cerr << std::endl;
    }

    /**
     * @brief Destructor of the Warning
     */
    Warning::~Warning()
    {
        if (!debug_mode)
            return;
        std::cerr << RESET << std::endl;
    }

    /**
     * @brief Print a warning message
     * @param pf The message to print
     * @return <b>Warning &</b> The warning object
     */
    Warning &Warning::operator<<(std::ostream &(*pf)(std::ostream &))
    {
        if (!debug_mode)
            return *this;
        std::cerr << pf;
        return *this;
    }
}
