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

# Find all .cpp and .hpp files in the src and include directories
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.hpp)

# Add the executable target
add_executable(MazeProject ${SOURCES} ${HEADERS})

# Link libraries or other dependencies if needed (e.g., if you're using any)
# target_link_libraries(MazeProject <LIBRARY_NAME>)

target_compile_options(MazeProject PRIVATE)
