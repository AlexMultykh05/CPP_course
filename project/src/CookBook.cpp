//
// Created by Alex Multykh on 28.04.2024.
//

#include "CookBook.hpp"


CookBook::CookBook(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << FAILED_OPEN_FILE << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    content_ = buffer.str();
}


void CookBook::printRecipe(const Dish &dish) {
    std::cout << RECIPE_FOR << dish.name << COLUMN_EOL;

    for (const auto &step : dish.recipe) {
        std::string trimmedStep = step;

        trimmedStep.erase(trimmedStep.begin(), std::find_if(trimmedStep.begin(), trimmedStep.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        trimmedStep.erase(std::find_if(trimmedStep.rbegin(), trimmedStep.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), trimmedStep.end());

        if (trimmedStep.front() == QUOTE) {
            trimmedStep.erase(trimmedStep.begin());
        }
        if (trimmedStep.back() == QUOTE) {
            trimmedStep.erase(trimmedStep.rbegin().base() - 1);
        }

        std::cout << trimmedStep << EOL;
    }
}


void CookBook::printDish(const Dish &dish) {
    std::cout << dish.name << SEMI_COLUMN << dish.type << SEMI_COLUMN << dish.cookingTime << MINUTES << INGREDIENTS_EOL;
    for (const auto &ingredient: dish.ingredients) {
        std::cout << TAB << ingredient << COMMA_EOL;
    }
    std::cout << EOL;
}


void CookBook::suggestDish(const std::vector<std::string> &inputIngredients) {
    std::vector<Dish> matchedDishes;

    std::istringstream f(content_);
    std::string line;
    std::vector<std::string> dishBuffer;

    while (std::getline(f, line)) {
        dishBuffer.push_back(line);
        if (line.find(CLOSED_CURLY_BRACKET) != std::string::npos) {
            Dish dish = parseDish(dishBuffer);
            if (matchIngredients(inputIngredients, dish.ingredients)) {
                matchedDishes.push_back(dish);
            }
            dishBuffer.clear();
        }
    }

    sortAndPrintDishes(matchedDishes);

    std::cout << ENTER_NUM_OF_DISH;
    int dishNumber;
    std::cin >> dishNumber;
    std::cout << EOL;

    if (dishNumber < MIN_DISH_NUM || dishNumber > matchedDishes.size()) {
        std::cout << INVALID_INPUT << matchedDishes.size() << DOT_EOL;
        return;
    }

    printRecipe(matchedDishes[dishNumber - 1]);
}

Dish CookBook::parseDish(std::vector<std::string>& dishBuffer) {
    Dish dish;
    while (!dishBuffer.empty()) {
        std::string dishLine = dishBuffer.front();
        dishBuffer.erase(dishBuffer.begin());

        if (dishLine.find(OPEN_CURLY_BRACKET) != std::string::npos) {
            continue;
        } else if (dishLine.find(CLOSED_CURLY_BRACKET) != std::string::npos) {
            break;
        } else if (dishLine.find(RECIPE) != std::string::npos) {
            parseRecipe(dishLine, dish, dishBuffer);
        } else {
            parseLine(dishLine, dish, dishBuffer);
        }
    }
    return dish;
}

bool CookBook::matchIngredients(const std::vector<std::string> &inputIngredients, const std::vector<std::string> &dishIngredients) {
    return std::ranges::all_of(inputIngredients, [&dishIngredients](const auto &inputIngredient) {
        return std::find(dishIngredients.begin(), dishIngredients.end(), inputIngredient) != dishIngredients.end();
    });
}

void CookBook::sortAndPrintDishes(std::vector<Dish>& matchedDishes) {
    std::sort(matchedDishes.begin(), matchedDishes.end(), [](const Dish &a, const Dish &b) {
        return a.cookingTime < b.cookingTime;
    });

    for (int i = 0; i < std::min(3, (int) matchedDishes.size()); ++i) {
        std::cout << std::to_string(i + 1) + DOT;
        printDish(matchedDishes[i]);
    }
}

std::string CookBook::parseName(const std::string &line, Dish &dish) {
    dish.name = line.substr(line.find(COLUMN) + 2);
    dish.name = dish.name.substr(1, dish.name.size() - 3);

    return dish.name;
}

std::string CookBook::parseType(const std::string &line, Dish &dish) {
    dish.type = line.substr(line.find(COLUMN) + 2);
    dish.type = dish.type.substr(1, dish.type.size() - 3);

    return dish.type;
}

int CookBook::parseTime(const std::string &line, Dish &dish) {
    std::string cookingTime = line.substr(line.find(COLUMN) + 2);
    cookingTime = cookingTime.substr(1, cookingTime.size() - 3);
    dish.cookingTime = std::stoi(cookingTime.substr(0, cookingTime.find(SPACE)));

    return dish.cookingTime;
}

std::vector<std::string> CookBook::parseIngredients(const std::string &line, Dish &dish) {
    std::string ingredients = line.substr(line.find(OPEN_INGREDIENTS) + 3);
    ingredients = ingredients.substr(0, ingredients.size() - 2);
    std::istringstream iss(ingredients);
    std::string ingredient;
    while (std::getline(iss, ingredient, COMMA)) {
        ingredient = ingredient.substr(2, ingredient.size() - 3);
        dish.ingredients.push_back(ingredient);
    }

    return dish.ingredients;
}

std::vector<std::string> CookBook::parseRecipe(const std::string &line, Dish &dish, std::vector<std::string>& dishBuffer) {
    std::string step = line.substr(line.find(COLUMN) + 2);
    step = step.substr(1, step.size() - 3);
    dish.recipe.push_back(step);

    while (!dishBuffer.empty()) {
        std::string nextLine = dishBuffer.front();
        if (nextLine.find(CLOSED_CURLY_BRACKET) != std::string::npos) {
            break;
        }
        dishBuffer.erase(dishBuffer.begin());
        step = nextLine.substr(2, nextLine.size() - 3);
        dish.recipe.push_back(step);
    }

    return dish.recipe;
}

void CookBook::parseLine(const std::string &line, Dish &dish, std::vector<std::string>& dishBuffer) {
    if (line.find(NAME_OF_DISH) != std::string::npos) {
        dish.name = parseName(line, dish);
    } else if (line.find(TYPE) != std::string::npos) {
        dish.type = parseType(line, dish);
    } else if (line.find(COOKING_TIME) != std::string::npos) {
        dish.cookingTime = parseTime(line, dish);
    } else if (line.find(INGREDIENTS) != std::string::npos) {
        dish.ingredients = parseIngredients(line, dish);
    } else if (line.find(RECIPE) != std::string::npos) {
        dish.recipe = parseRecipe(line, dish, dishBuffer);
    }
}