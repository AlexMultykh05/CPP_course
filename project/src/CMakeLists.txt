cmake_minimum_required(VERSION 3.28)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(project main.cpp
        CookBook.hpp
        CookBook.cpp
        Dish.hpp
        Constants.hpp
)

include_directories(/Users/alexmultykh/Library/Caches/Homebrew/downloads/nlohmann-json/3.11.3/include)