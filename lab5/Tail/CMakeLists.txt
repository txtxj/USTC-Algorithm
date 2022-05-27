cmake_minimum_required(VERSION 3.21)
project(Tail)

add_definitions(-DDEBUG)
#add_definitions(-DBIGINTDEBUG)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tail
        tail.cpp)
