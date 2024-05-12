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

constexpr char FAILED_OPEN_FILE[] = "Failed to open file.";
constexpr char ENTER_NUM_OF_DISH[] = "Enter the number of the dish you want the recipe for: ";
constexpr char ENTER_INGREDIENTS[] = "Enter ingredients (separated by comma): ";
constexpr char INVALID_INPUT[] = "Invalid input. Please enter a number between 1 and ";
constexpr char NAME_OF_DISH[] = "name_of_dish";
constexpr char RECIPE_FOR[] = "Recipe for ";
constexpr char TYPE[] = "type";
constexpr char COOKING_TIME[] = "cooking_time";
constexpr char INGREDIENTS[] = "ingredients";
constexpr char INGREDIENTS_EOL[] = "ingredients:\n";
constexpr char RECIPE[] = "recipe";
constexpr char MINUTES_COLUMN[] = " minutes; ";
constexpr char MINUTE[] = "minutes";
constexpr char MINUTES[] = "minutes";
constexpr char HOUR[] = "hour";
constexpr char HOURS[] = "hours";
constexpr char OPEN_CURLY_BRACKET = '{';
constexpr char CLOSED_CURLY_BRACKET = '}';
constexpr char OPEN_INGREDIENTS[] = ": [";
constexpr char COLUMN[] = ": ";
constexpr char DOT[] = ". ";
constexpr char SEMI_COLUMN[] = "; ";
constexpr char COMMA_EOL[] = ",\n";
constexpr char COLUMN_EOL[] = ":\n";
constexpr char DOT_EOL[] = ".\n";
constexpr char COMMA = ',';
constexpr char SPACE = ' ';
constexpr char TAB = '\t';
constexpr char EOL = '\n';
constexpr char QUOTE = '"';
constexpr int MIN_DISH_NUM = 1;
constexpr int MAX_DISH_NUM = 10;
constexpr int MINUTES_IN_HOUR = 60;
constexpr int MIN_NUMBER = 0;


struct Dish {
    std::string name;
    std::string type;
    std::string formattedCookingTime;
    int cookingTime;
    std::vector<std::string> ingredients;
    std::vector<std::string> recipe;
};


class CookBook {
private:
    std::string content_;

public:
    explicit CookBook(const std::string& filename);

    static void printRecipe(const Dish &dish);

    static void printDish(const Dish &dish);

    void suggestDish(const std::vector<std::string> &inputIngredients);

    static Dish parseDish(std::vector<std::string>& dishBuffer);

    static bool matchIngredients(const std::vector<std::string> &inputIngredients, const std::vector<std::string> &dishIngredients);

    static void sortAndPrintDishes(std::vector<Dish> &matchedDishes);

    static std::string parseName(const std::string &line, Dish &dish);

    static std::string parseType(const std::string &line, Dish &dish);

    static int parseCookingTime(const std::string &line, Dish &dish);

    static std::vector<std::string> parseIngredients(const std::string &line, Dish &dish);

    static std::vector<std::string> parseRecipe(const std::string &line, Dish &dish, std::vector<std::string>& dishBuffer);

    static void parseLine(const std::string &line, Dish &dish, std::vector<std::string>& dishBuffer);

};


#endif //PROJECT_COOKBOOK_HPP
