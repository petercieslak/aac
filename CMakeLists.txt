cmake_minimum_required(VERSION 3.26)
project(aac)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(aac
        main.cpp
        main.h
        Multigraph.cpp
        MultigraphReader.cpp)
