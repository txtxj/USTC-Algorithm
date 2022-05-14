cmake_minimum_required(VERSION 3.21)
project(MST)

add_definitions(-DDEBUG)

set(CMAKE_CXX_STANDARD 14)

add_executable(MST
        mst.cpp)
