#include <iostream>
#include "CookBook.hpp"


std::vector<std::string> readIngredients() {
    std::string line;
    std::cout << ENTER_INGREDIENTS;
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
    std::vector<std::string> inputIngredients = readIngredients();

    CookBook myCookBook("/Users/alexmultykh/Desktop/multykho/project/src/cookbook_db.json");

    while (true) {
        bool dishesSuggested = myCookBook.suggestDish(inputIngredients);

        if (!dishesSuggested) {
            std::cout << "Enter 'end' to end the program or 'add' to add more ingredients: ";
            std::string input;
            std::getline(std::cin, input);

            if (input == "end") {
                break;
            } else if (input == "add") {
                std::cout << "Add more products for finding a dish (separated by comma): ";
                std::vector<std::string> moreIngredients = readIngredients();
                inputIngredients.insert(inputIngredients.end(), moreIngredients.begin(), moreIngredients.end());
                continue;
            }
        } else {
            break;
        }
    }


//    std::ifstream file("/Users/alexmultykh/Desktop/multykho/project/src/cookbook_db.json");
//    std::string line;
//    std::vector<std::string> dishBuffer;
//    int dishNum = 1;
//
//    while (std::getline(file, line)) {
//        dishBuffer.push_back(line);
//        if (line.find("}") != std::string::npos) {
//            // Assuming parseDish is accessible and can take a vector of strings
//            Dish dish = CookBook::parseDish(dishBuffer);
//            std::cout << dishNum << ". ";
//            CookBook::printDish(dish);
//            dishBuffer.clear();
//            dishNum++;
//        }
//    }


    return 0;
}