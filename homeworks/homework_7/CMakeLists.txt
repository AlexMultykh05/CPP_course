cmake_minimum_required(VERSION 3.26)
project(6th_hw)

set(CMAKE_CXX_STANDARD 17)

add_executable(6th_hw main.cpp
        Node.h
        Node.cpp
        Expression.cpp
        Expression.h
        Exception.h
        Parser.h
        Parser.cpp
        Reader.h)
