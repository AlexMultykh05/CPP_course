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

constexpr char OPEN_CURLY_BRACKET = '{';
constexpr char CLOSED_CURLY_BRACKET = '}';
constexpr char COMMA = ',';
constexpr char OPEN_INGREDIENTS[] = ": [";
constexpr char INGREDIENTS[] = "ingredients";


struct Dish {
    std::string name;
    std::string type;
    int cookingTime;
    std::vector<std::string> ingredients;
    std::vector<std::string> recipe;
};


class CookBook {
private:
    std::string content_;

public:
    CookBook(const std::string& filename);

    const std::string &name() const;

    const std::string &type() const;

    unsigned short time() const;

    const std::vector<std::string> &ingredients() const;

    const std::vector<std::string> &recipe() const;

    void suggestDishes(std::ostream &os = std::cout) const;

    static void storeCurrentIngredients(std::vector<std::string> &currentDishIngredients, std::istringstream &iss,
                                 std::string &ingredient);

    static bool checkIfMatchIngredients(const std::vector<std::string> &inputIngredients, std::vector<std::string> &currentDishIngredients);

    static void printRecipes(const std::vector<CookBook> &books, std::ostream &os = std::cout);

    static void printDish(const Dish &dish);

    void findDish(const std::vector<std::string> &inputIngredients);

    static std::string parseName(const std::string &line, Dish &dish);

    static std::string parseType(const std::string &line, Dish &dish);

    static int parseTime(const std::string &line, Dish &dish);

    static std::vector<std::string> parseIngredients(const std::string &line, Dish &dish);

    static std::vector<std::string> parseRecipe(const std::string &line, Dish &dish);

    static void parseLine(const std::string &line, Dish &dish);

};

//
//inline const std::string &CookBook::name() const {
//    return name_;
//}
//
//inline const std::string &CookBook::type() const {
//    return type_;
//}
//
//inline unsigned short CookBook::time() const {
//    return time_;
//}
//
//inline const std::vector<std::string> &CookBook::ingredients() const {
//    return ingredients_;
//}
//
//inline const std::vector<std::string> &CookBook::recipe() const {
//    return recipe_;
//}


#endif //PROJECT_COOKBOOK_HPP
