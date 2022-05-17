cmake_minimum_required(VERSION 3.21)
project(Accessibility)

add_definitions(-DDEBUG)

set(CMAKE_CXX_STANDARD 14)

add_executable(Accessibility
        access.cpp)
