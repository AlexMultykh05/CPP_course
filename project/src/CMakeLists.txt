cmake_minimum_required(VERSION 3.28)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(project main.cpp
        CookBook.hpp
        CookBook.cpp)
