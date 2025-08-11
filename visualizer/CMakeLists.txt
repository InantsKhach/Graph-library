cmake_minimum_required(VERSION 3.10)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(MazeVisualizer
    main.cpp
    MainWindow.cpp
    MazeWidget.cpp
)

target_link_libraries(MazeVisualizer
    PRIVATE
        Qt5::Widgets
        MazeCore
)

target_include_directories(MazeVisualizer PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
