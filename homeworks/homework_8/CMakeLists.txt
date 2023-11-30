cmake_minimum_required(VERSION 3.26)
project(5th_hw)

set(CMAKE_CXX_STANDARD 17)

add_executable(5th_hw main.cpp
        Title.cpp
        Title.h
        Database.h
        Queries.h
        Database.cpp
        Queries.cpp
        Actor.h
        Actor.cpp)
