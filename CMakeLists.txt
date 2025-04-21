# Configure CMake for the Jetpack project
cmake_minimum_required(VERSION 3.10)
project(jetpack VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DEBUG_MODE "Enable DEBUG mode" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_compile_options(-Werror -Wextra -Wno-unused-result)

if(DEBUG_MODE)
    message(STATUS "DEBUG mode enabled")
    add_compile_options(-g3 -DDEBUG_MODE)
    set(CMAKE_BUILD_TYPE Debug)
else()
    add_compile_options(-O3)
    set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB_RECURSE ALL_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
set(CLIENT_SOURCES "")
set(SERVER_SOURCES "")
foreach(file ${ALL_SOURCES})
    if(NOT file MATCHES "/server/")
        list(APPEND CLIENT_SOURCES ${file})
    endif()
    if(NOT file MATCHES "/client/")
        list(APPEND SERVER_SOURCES ${file})
    endif()
endforeach()

add_executable(jetpack_client ${CLIENT_SOURCES})
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics window system audio)
target_link_libraries(jetpack_client sfml-graphics sfml-window sfml-system sfml-audio)

add_executable(jetpack_server ${SERVER_SOURCES})

# Custom rules for the project
add_custom_target(client
        COMMAND ${CMAKE_COMMAND} --build . --target jetpack_client
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Build client"
)

add_custom_target(server
        COMMAND ${CMAKE_COMMAND} --build . --target jetpack_server
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Build server"
)

# Makefile rules
add_custom_target(fclean
        COMMAND ${CMAKE_COMMAND} --build . --target clean
        COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_SOURCE_DIR}/unit_tests*
        COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_SOURCE_DIR}/tests/unit_tests*
        COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_SOURCE_DIR}/vgcore*
        COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_SOURCE_DIR}/*.log
        #COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
        COMMENT "Remove all generated files (full clean)"
)

add_custom_target(re
        COMMAND ${CMAKE_COMMAND} --build . --target fclean
        COMMAND ${CMAKE_COMMAND} -DDEBUG_MODE=OFF ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Full clean and rebuild"
)

# Debug mode rules
add_custom_target(debug
        COMMAND ${CMAKE_COMMAND} -DDEBUG_MODE=ON ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Build in DEBUG mode"
)

add_custom_target(re_debug
        COMMAND ${CMAKE_COMMAND} --build . --target fclean
        COMMAND ${CMAKE_COMMAND} -DDEBUG_MODE=ON ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Full clean and rebuild in DEBUG mode"
)

# Unit tests rules
add_custom_target(unit_tests
        COMMAND make unit_tests --no-print-directory -C./tests/
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Build unit tests"
)

add_custom_target(tests_run
        COMMAND make tests_run --no-print-directory -C./tests/
        COMMAND gcovr
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Build and run unit tests"
)

# Documentation rules
add_custom_target(doc
        COMMAND mkdir -p docs/html
        COMMAND mkdir -p docs/tests
        COMMAND doxygen Doxyfile
        COMMAND gcovr --branch --html-details docs/tests/test.html
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generate documentation"
)