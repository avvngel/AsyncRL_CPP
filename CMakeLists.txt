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

# Define source files
file(GLOB SOURCES "src/*.cpp")

# Global Compiler flags
add_compile_options(-g -Wall -Wextra -Werror -pedantic)

# Define libraries

