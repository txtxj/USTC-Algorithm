cmake_minimum_required(VERSION 3.21)
project(Tail)
project(Tail_small)

add_definitions(-DDEBUG)
#add_definitions(-DBIGINTDEBUG)
add_definitions(-DFILEREAD)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tail
        tail.cpp)

add_executable(Tail_small
        tail_small.cpp)