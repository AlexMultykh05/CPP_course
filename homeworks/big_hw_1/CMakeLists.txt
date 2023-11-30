cmake_minimum_required(VERSION 3.26)
project(big_hw_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(bid_hw_1 main.cpp
        Node.h
        Node.cpp
        Expression.h
        Expression.cpp
        Parser.h
        Parser.cpp
        Reader.h
        Reader.cpp
        Neighbors.h
        Neighbors.cpp
        Symbol.h
        Symbol.cpp
        Result.h
        Exception.h
)