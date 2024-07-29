cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_program
        test.cpp
        AdjacencyListGraph.cpp
        AdjacencyMatrixGraph.cpp
        Algorithms.cpp
        MazeCellPredicateStraightLine.cpp
        MazeCellSimplePredicate.cpp
        MazeGraphRepresentation.cpp
        MazeWithBoxes.cpp
        MazeWithWalls.cpp
        RandomizedDFS.cpp
        RecursiveDivision.cpp
        # Add all your source files here
)