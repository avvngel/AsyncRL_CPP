# Version Requirement
cmake_minimum_required( VERSION 3.26 )

# Project details
project(AsyncRL++ VERSION 1.0.0 DESCRIPTION "C++ library for designing and implementing asynchronous reinforcement learning frameworks.")

# Set standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Modify Search Path
list(APPEND CMAKE_PREFIX_PATH "/opt/libtorch")

# Find Dependencies
find_package(Torch REQUIRED)
find_package(Doxygen QUIET)

# Option to build documentation (Developers only), default is OFF
option(BUILD_DOC "Build documentation" OFF)

if (DOXYGEN_FOUND AND BUILD_DOC)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs)

    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()

# Set Library Name
set(LIBRARY_NAME "AsyncRL")

# Global Compiler flags
add_compile_options(-g -Wall -Wextra -Werror -pedantic -std=c++20)

# Enable CTest
enable_testing()

# Define libraries
add_subdirectory(src)
add_subdirectory(tests)
