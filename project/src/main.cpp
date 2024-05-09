#include <iostream>
#include "CookBook.hpp"


std::vector<std::string> readIngredients() {
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> ingredients;
    std::stringstream ss(line);
    std::string ingredient;

    while (std::getline(ss, ingredient, COMMA)) {
        ingredient.erase(ingredient.begin(), std::find_if(ingredient.begin(), ingredient.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        ingredient.erase(std::find_if(ingredient.rbegin(), ingredient.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), ingredient.end());

        ingredients.push_back(ingredient);
    }

    return ingredients;
}

int main() {
    std::cout << ENTER_INGREDIENTS;
    std::vector<std::string> inputIngredients = readIngredients();

    CookBook myCookBook("/Users/alexmultykh/Desktop/multykho/project/src/cookbook_db.json");

    myCookBook.suggestDish(inputIngredients);

    return 0;
}