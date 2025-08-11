# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MazeProject VERSION 1.0)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source and header directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Add include directories
include_directories(${INCLUDE_DIR})

# Gather sources for core library
file(GLOB CORE_SOURCES ${SRC_DIR}/*.cpp)
list(REMOVE_ITEM CORE_SOURCES ${SRC_DIR}/test.cpp)

# Core library with algorithms and data structures
add_library(MazeCore ${CORE_SOURCES})
target_include_directories(MazeCore PUBLIC ${INCLUDE_DIR})

# Simple CLI executable for manual testing
add_executable(MazeCLI ${SRC_DIR}/test.cpp)
target_link_libraries(MazeCLI MazeCore)

# Build the Qt visualizer
add_subdirectory(visualizer)

# Link libraries or other dependencies if needed (e.g., if you're using any)
# target_link_libraries(MazeProject <LIBRARY_NAME>)

target_compile_options(MazeCLI PRIVATE)
