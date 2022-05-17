cmake_minimum_required(VERSION 3.21)
project(Floyd)
project(Johnson)

add_definitions("-DDEBUG")

set(CMAKE_CXX_STANDARD 14)

add_executable(Floyd
        floyd.cpp)

add_executable(Johnson
        johnson.cpp)