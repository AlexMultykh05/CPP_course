//
// Created by Alex Multykh on 29.06.2024.
//

#ifndef PROJECT_DISH_HPP
#define PROJECT_DISH_HPP

#include <string>
#include <vector>

struct Dish {
    std::string name;
    std::string type;
    std::string formattedCookingTime;
    int cookingTime;
    std::vector<std::string> ingredients;
    std::vector<std::string> recipe;
};

#endif //PROJECT_DISH_HPP
