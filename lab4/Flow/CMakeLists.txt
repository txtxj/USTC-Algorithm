cmake_minimum_required(VERSION 3.21)
project(Shortest)
project(Fattest)

add_definitions(-DDEBUG)

set(CMAKE_CXX_STANDARD 17)

add_executable(Shortest
        shortest.cpp)

add_executable(Fattest
        fattest.cpp)