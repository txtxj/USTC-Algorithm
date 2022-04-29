cmake_minimum_required(VERSION 3.21)
project(Largest)

add_definitions(-DDEBUG)

set(CMAKE_CXX_STANDARD 14)

add_executable(Largest
        largest.cpp)
