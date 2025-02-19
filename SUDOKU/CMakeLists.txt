cmake_minimum_required(VERSION 3.10)

project(Sudoku VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_STATIC_LIBRARIES TRUE)
add_definitions(-DSFML_STATIC)

find_package(SFML REQUIRED COMPONENTS System Window Graphics Network)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found!")
endif()

set(SOURCES 
    src/main.cpp src/Board.cpp src/Game.cpp)
add_executable(Sudoku ${SOURCES})

target_link_libraries(Sudoku PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
    opengl32
    winmm
    gdi32
)

target_include_directories(Sudoku PRIVATE SFML_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
