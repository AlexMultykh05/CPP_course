//
// Created by Alex Multykh on 28.04.2024.
//

#include "CookBook.hpp"


CookBook::CookBook(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    content_ = buffer.str();
}


void CookBook::suggestDishes(std::ostream &os) const {

}


void CookBook::printRecipes(const std::vector<CookBook> &books, std::ostream &os) {

}

void CookBook::printDish(const std::vector<std::string> &inputIngredients) {
    std::istringstream f(content_);
    std::string line;
    bool printedDish = false;
    std::vector<std::string> currentDishIngredients;
    std::vector<std::string> dishBuffer;

    while (std::getline(f, line)) {
        dishBuffer.push_back(line);
        if (line.find(INGREDIENTS) != std::string::npos) {
            std::string ingredients = line.substr(line.find(OPEN_INGREDIENTS) + 3);
            ingredients = ingredients.substr(0, ingredients.size() - 2);
            std::istringstream iss(ingredients);
            std::string ingredient;
            while (std::getline(iss, ingredient, COMMA)) {
                ingredient = ingredient.substr(2, ingredient.size() - 3);
                currentDishIngredients.push_back(ingredient);
            }
            if (std::equal(inputIngredients.begin(), inputIngredients.begin() + 3, currentDishIngredients.begin())) {
                if (!printedDish) {
                    for (auto &dishLine : dishBuffer) {
                        if (dishLine.find(OPEN_CURLY_BRACKET) != std::string::npos) {
                            continue;
                        } else if (dishLine.find(CLOSED_CURLY_BRACKET) != std::string::npos) {
                            break;
                        } else {
                            parseLine(dishLine);
                        }
                    }
                    printedDish = true;
                }
            } else {
                currentDishIngredients.clear();
                dishBuffer.clear();
            }
        }
        if (line.find(CLOSED_CURLY_BRACKET) != std::string::npos) {
            dishBuffer.clear();
        }
    }
}


void CookBook::parseLine(std::string &line){
    if (line.find("name_of_dish") != std::string::npos) {
        std::string dishName = line.substr(line.find(": ") + 2);
        dishName = dishName.substr(1, dishName.size() - 3);
        std::cout << dishName << "; ";
    } else if (line.find("type") != std::string::npos) {
        std::string dishType = line.substr(line.find(": ") + 2);
        dishType = dishType.substr(1, dishType.size() - 3);
        std::cout << dishType << "; ";
    } else if (line.find("cooking_time") != std::string::npos) {
        std::string cookingTime = line.substr(line.find(": ") + 2);
        cookingTime = cookingTime.substr(1, cookingTime.size() - 3);
        std::cout << cookingTime << "; ingredients:\n";
    } else if (line.find("ingredients") != std::string::npos) {
        std::string ingredients = line.substr(line.find(": [") + 3);
        ingredients = ingredients.substr(0, ingredients.size() - 2);
        std::istringstream iss(ingredients);
        std::string ingredient;
        while (std::getline(iss, ingredient, ',')) {
            ingredient = ingredient.substr(2, ingredient.size() - 3);
            std::cout << (iss.eof() ? "\t" + ingredient + "\n" : "\t" + ingredient + ",\n");
        }
    }
}

//void CookBook::read_json(std::vector<CookBook> &books, std::istream &is) {
//
//}