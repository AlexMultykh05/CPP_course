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


void CookBook::printRecipes(const std::vector<CookBook> &books, std::ostream &os) {

}

void CookBook::storeCurrentIngredients(std::vector<std::string> &currentDishIngredients, std::istringstream &iss,
                                       std::string &ingredient) {
    while (std::getline(iss, ingredient, COMMA)) {
        ingredient = ingredient.substr(2, ingredient.size() - 3);
        currentDishIngredients.push_back(ingredient);
    }
}

bool CookBook::checkIfMatchIngredients(const std::vector<std::string> &inputIngredients,
                                       std::vector<std::string> &currentDishIngredients) {
    bool allIngredientsMatch = true;
    for (const auto &inputIngredient: inputIngredients) {
        if (std::find(currentDishIngredients.begin(), currentDishIngredients.end(), inputIngredient) ==
            currentDishIngredients.end()) {
            allIngredientsMatch = false;
            break;
        }
    }
    return allIngredientsMatch;
}


void CookBook::printDish(const Dish &dish) {
    std::cout << dish.name << "; " << dish.type << "; " << dish.cookingTime << " minutes; " << "ingredients:\n";
    for (const auto &ingredient: dish.ingredients) {
        std::cout << "\t" << ingredient << ",\n";
    }
    std::cout << "\n";
}


void CookBook::findDish(const std::vector<std::string> &inputIngredients) {
    std::istringstream f(content_);
    std::string line;
    std::vector<std::string> currentDishIngredients;
    std::vector<std::string> dishBuffer;
    std::vector<Dish> matchedDishes;

    while (std::getline(f, line)) {
        dishBuffer.push_back(line);
        if (line.find(INGREDIENTS) != std::string::npos) {
            std::string ingredients = line.substr(line.find(OPEN_INGREDIENTS) + 3);
            ingredients = ingredients.substr(0, ingredients.size() - 2);
            std::istringstream iss(ingredients);
            std::string ingredient;

            storeCurrentIngredients(currentDishIngredients, iss, ingredient);

            bool allIngredientsMatch = checkIfMatchIngredients(inputIngredients, currentDishIngredients);

            if (allIngredientsMatch) {
                Dish dish;
                for (auto &dishLine: dishBuffer) {
                    if (dishLine.find(OPEN_CURLY_BRACKET) != std::string::npos) {
                        continue;
                    } else if (dishLine.find(CLOSED_CURLY_BRACKET) != std::string::npos) {
                        break;
                    } else {
                        parseLine(dishLine, dish);
                    }
                }
                matchedDishes.push_back(dish);
            }
        }
        if (line.find(CLOSED_CURLY_BRACKET) != std::string::npos) {
            dishBuffer.clear();
            currentDishIngredients.clear();
        }
    }

    std::sort(matchedDishes.begin(), matchedDishes.end(), [](const Dish &a, const Dish &b) {
        return a.cookingTime < b.cookingTime;
    });

    for (int i = 0; i < std::min(3, (int) matchedDishes.size()); ++i) {
        std::cout << std::to_string(i + 1) + ". ";
        printDish(matchedDishes[i]);
    }
}


std::string CookBook::parseName(const std::string &line, Dish &dish) {
    dish.name = line.substr(line.find(": ") + 2);
    dish.name = dish.name.substr(1, dish.name.size() - 3);

    return dish.name;
}

std::string CookBook::parseType(const std::string &line, Dish &dish) {
    dish.type = line.substr(line.find(": ") + 2);
    dish.type = dish.type.substr(1, dish.type.size() - 3);

    return dish.type;
}

int CookBook::parseTime(const std::string &line, Dish &dish) {
    std::string cookingTime = line.substr(line.find(": ") + 2);
    cookingTime = cookingTime.substr(1, cookingTime.size() - 3);
    dish.cookingTime = std::stoi(cookingTime.substr(0, cookingTime.find(" ")));

    return dish.cookingTime;
}

std::vector<std::string> CookBook::parseIngredients(const std::string &line, Dish &dish) {
    std::string ingredients = line.substr(line.find(": [") + 3);
    ingredients = ingredients.substr(0, ingredients.size() - 2);
    std::istringstream iss(ingredients);
    std::string ingredient;
    while (std::getline(iss, ingredient, ',')) {
        ingredient = ingredient.substr(2, ingredient.size() - 3);
        dish.ingredients.push_back(ingredient);
    }

    return dish.ingredients;
}

std::vector<std::string> CookBook::parseRecipe(const std::string &line, Dish &dish) {
    std::string recipe = line.substr(line.find(": [") + 3);
    recipe = recipe.substr(0, recipe.size() - 2);
    std::istringstream iss(recipe);
    std::string step;
    while (std::getline(iss, step, ',')) {
        step = step.substr(2, step.size() - 3);
        dish.recipe.push_back(step);
    }

    return dish.recipe;
}

void CookBook::parseLine(const std::string &line, Dish &dish) {
    if (line.find("name_of_dish") != std::string::npos) {
        dish.name = parseName(line, dish);
    } else if (line.find("type") != std::string::npos) {
        dish.type = parseType(line, dish);
    } else if (line.find("cooking_time") != std::string::npos) {
        dish.cookingTime = parseTime(line, dish);
    } else if (line.find("ingredients") != std::string::npos) {
        dish.ingredients = parseIngredients(line, dish);
    } else if (line.find("recipe") != std::string::npos) {
        dish.recipe = parseRecipe(line, dish);
    }
}