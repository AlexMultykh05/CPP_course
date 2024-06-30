/**
 * @file Dish.hpp
 * @author Alex Multykh
 * @date 29.06.2024
 */

//
// Created by Alex Multykh on 29.06.2024.
//

#ifndef PROJECT_DISH_HPP
#define PROJECT_DISH_HPP

#include <string>
#include <vector>


/**
 * @struct Dish
 * @brief Struct representing a dish.
 */
struct Dish {
    /**
     * @brief Name of the dish.
     */
    std::string name;

    /**
     * @brief Type of the dish.
     */
    std::string type;

    /**
     * @brief Formatted cooking time of the dish.
     */
    std::string formattedCookingTime;

    /**
     * @brief Cooking time of the dish in minutes.
     */
    int cookingTime;

    /**
     * @brief Vector of ingredients of the dish.
     */
    std::vector<std::string> ingredients;

    /**
     * @brief Vector of recipe of the dish.
     */
    std::vector<std::string> recipe;
};

#endif //PROJECT_DISH_HPP
