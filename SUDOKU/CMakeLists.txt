cmake_minimum_required(VERSION 3.10)

project(Sudoku VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/Users/kotko/Documents/libs/SFML-3.0.0/lib/cmake/SFML")

set(SFML_STATIC_LIBRARIES TRUE)
add_definitions(-DSFML_STATIC)

find_package(SFML REQUIRED COMPONENTS System Window Graphics Network)

include_directories("C:/Users/kotko/Documents/libs/SFML-3.0.0/include")
link_directories("C:/Users/kotko/Documents/libs/SFML-3.0.0/lib")

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found!")
endif()

file(GLOB SOURCES "src/*.cpp")

add_executable(Sudoku ${SOURCES})

target_link_libraries(Sudoku PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
    opengl32
    winmm
    gdi32
)

target_include_directories(Sudoku PRIVATE "C:/Users/kotko/Documents/libs/SFML-3.0.0/include" "C:/Users/kotko/Desktop/SUDOKU/include")
