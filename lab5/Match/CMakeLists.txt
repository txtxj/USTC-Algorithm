cmake_minimum_required(VERSION 3.21)
project(Match)

add_definitions(-DDEBUG)

set(CMAKE_CXX_STANDARD 17)

add_executable(Match match.cpp)
