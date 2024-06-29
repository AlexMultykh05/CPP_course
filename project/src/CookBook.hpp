//
// Created by Alex Multykh on 28.04.2024.
//

#ifndef PROJECT_COOKBOOK_HPP
#define PROJECT_COOKBOOK_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include "Dish.hpp"
#include "Constants.hpp"

class CookBook {
private:
    std::string content_;

public:
    explicit CookBook(const std::string& filename);

    static void printRecipe(const Dish &dish);

    static void printDish(const Dish &dish);

    bool suggestDish(const std::vector<std::string> &inputIngredients);

    static void sortDishes(const std::string &method, std::vector<Dish> &dishes);

    static Dish parseDish(std::vector<std::string>& dishBuffer);

    static bool matchIngredients(const std::vector<std::string> &inputIngredients, const std::vector<std::string> &dishIngredients);

    static std::string parseName(const std::string &line, Dish &dish);

    static std::string parseType(const std::string &line, Dish &dish);

    static int parseCookingTime(const std::string &line, Dish &dish);

    static std::vector<std::string> parseIngredients(std::vector<std::string> &dishBuffer, Dish &dish);

    static std::vector<std::string> parseRecipe(std::vector<std::string> &dishBuffer, Dish &dish);

    static void parseLine(const std::string &line, Dish &dish, std::vector<std::string>& dishBuffer);

    static nlohmann::json loadJson();

    static void writeJsonObject(const nlohmann::json& j);

    static void addDish(const Dish& newDish);

    void deleteDish(const std::string& dishName);

    static void editDish(const std::string& dishName, const Dish& updatedDish);

    static void viewDish(const std::string& dishName);

    static void printArray(const nlohmann::json &array, const std::string &label);
};


#endif //PROJECT_COOKBOOK_HPP
