cmake_minimum_required(VERSION 3.16.4)
project(maze)

include_directories(include)

add_executable(generate src/main.cpp src/maze.cpp)
add_executable(solve src/solve.cpp)

