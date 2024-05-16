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


bool isNotSpace(unsigned char ch) {
    return !std::isspace(ch);
}


void CookBook::printRecipe(const Dish &dish) {
    std::cout << RECIPE_FOR << dish.name << COLUMN_EOL;

    for (const auto &step: dish.recipe) {
        std::string trimmedStep = step;

        trimmedStep.erase(trimmedStep.begin(), std::find_if(trimmedStep.begin(), trimmedStep.end(), isNotSpace));
        trimmedStep.erase(std::find_if(trimmedStep.rbegin(), trimmedStep.rend(), isNotSpace).base(), trimmedStep.end());

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
    bool last = false;
    std::cout << dish.name << SEMI_COLUMN << dish.type << SEMI_COLUMN << dish.formattedCookingTime << INGREDIENTS_EOL;
    for (const auto &ingredient: dish.ingredients) {
        if (ingredient == dish.ingredients.back()) {
            last = true;
        }
        std::cout << TAB << ingredient;
        std::cout << (last ? "" : COMMA_EOL);
    }
    std::cout << EOL;
}


bool CookBook::checkIfEmpty(const std::vector<Dish> &matchedDishes) {
    if (matchedDishes.empty()) {
        std::cout << "I am sorry, I do not have a dish to suggest." << std::endl;
        return false;
    }
}


bool CookBook::suggestDish(const std::vector<std::string> &inputIngredients) {
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

    if (matchedDishes.empty()) {
        std::cout << "I am sorry, I do not have a dish to suggest." << std::endl;
        return false;
    }

    std::cout << "Choose sorting (type/time/alphabet): ";
    std::string sortingMethod;
    std::cin >> sortingMethod;

    sortDishes(sortingMethod, matchedDishes);

    int start = 0;
    int end = std::min(MAX_DISH_NUM, (int) matchedDishes.size());

    while (true) {
        for (int i = start; i < end; ++i) {
            std::cout << std::to_string(i + 1) + DOT;
            printDish(matchedDishes[i]);
        }

        std::cout << "Enter the number of the dish for the recipe or 'more' to load more dishes: ";
        std::string input;
        std::cin >> input;

        if (input == "more") {
            start = end;
            end = std::min(end + MAX_DISH_NUM, (int) matchedDishes.size());
            if (start == end) {
                std::cout << "No more dishes to load." << std::endl;
            }
        } else {
            int dishNumber = std::stoi(input);
            if (dishNumber < MIN_DISH_NUM || dishNumber > end) {
                std::cout << INVALID_INPUT << end << DOT_EOL;
            } else {
                printRecipe(matchedDishes[dishNumber - 1]);
                break;
            }
        }
    }

    return true;
}


void CookBook::sortDishes(const std::string& method, std::vector<Dish>& dishes) {
    if (method == "type") {
        std::sort(dishes.begin(), dishes.end(), [](const Dish& a, const Dish& b) {
            return a.type < b.type;
        });
    } else if (method == "time") {
        std::sort(dishes.begin(), dishes.end(), [](const Dish& a, const Dish& b) {
            return a.cookingTime < b.cookingTime;
        });
    } else if (method == "alphabet") {
        std::sort(dishes.begin(), dishes.end(), [](const Dish& a, const Dish& b) {
            return a.name < b.name;
        });
    }
}


Dish CookBook::parseDish(std::vector<std::string> &dishBuffer) {
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


bool CookBook::matchIngredients(const std::vector<std::string> &inputIngredients,
                                const std::vector<std::string> &dishIngredients) {
    int matchCount = 0;
    for (const auto &inputIngredient: inputIngredients) {
        if (std::find(dishIngredients.begin(), dishIngredients.end(), inputIngredient) != dishIngredients.end()) {
            matchCount++;
        }
    }
    return matchCount >= 2;
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


int CookBook::computingTime(const std::string &cookingTime) {
    std::istringstream iss(cookingTime);
    std::string word;
    int totalMinutes = MIN_NUMBER;
    int value;
    while (iss >> value >> word) {
        if (word == HOUR || word == HOURS) {
            totalMinutes += value * MINUTES_IN_HOUR;
        } else if (word == MINUTE || word == MINUTES) {
            totalMinutes += value;
        }
    }

    return totalMinutes;
}


int CookBook::parseCookingTime(const std::string &line, Dish &dish) {
    std::string cookingTime = line.substr(line.find(COLUMN) + 2);
    cookingTime = cookingTime.substr(1, cookingTime.size() - 3);

    int totalMinutes = computingTime(cookingTime);

    dish.cookingTime = totalMinutes;

    if (totalMinutes <= MINUTES_IN_HOUR) {
        dish.formattedCookingTime = std::to_string(totalMinutes) + MINUTES_COLUMN;
    } else {
        int hours = totalMinutes / MINUTES_IN_HOUR;
        int minutes = totalMinutes % MINUTES_IN_HOUR;
        dish.formattedCookingTime = std::to_string(hours) + (hours == MIN_DISH_NUM ? HOUR_SPACES : HOURS_SPACE) +
                                    (minutes > 0 ? SPACE + std::to_string(minutes) + MINUTES_COLUMN : SEMI_COLUMN);
    }

    return totalMinutes;
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


std::vector<std::string>
CookBook::parseRecipe(const std::string &line, Dish &dish, std::vector<std::string> &dishBuffer) {
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


void CookBook::parseLine(const std::string &line, Dish &dish, std::vector<std::string> &dishBuffer) {
    if (line.find(NAME_OF_DISH) != std::string::npos) {
        dish.name = parseName(line, dish);
    } else if (line.find(TYPE) != std::string::npos) {
        dish.type = parseType(line, dish);
    } else if (line.find(COOKING_TIME) != std::string::npos) {
        dish.cookingTime = parseCookingTime(line, dish);
    } else if (line.find(INGREDIENTS) != std::string::npos) {
        dish.ingredients = parseIngredients(line, dish);
    } else if (line.find(RECIPE) != std::string::npos) {
        dish.recipe = parseRecipe(line, dish, dishBuffer);
    }
}
