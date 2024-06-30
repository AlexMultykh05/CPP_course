//
// Created by Alex Multykh on 28.04.2024.
//

/**
 * @file CookBook.cpp
 * @author Alex Multykh
 * @date 28.04.2024
 */

#include "CookBook.hpp"


/**
 * @brief Converts a Dish object to a JSON object.
 *
 * @param j JSON object to hold the result.
 * @param d Dish object to convert.
 */
namespace nlohmann {
    void to_json(json& j, const Dish& d) {
        j = json{{"name", d.name}, {"type", d.type}, {"formattedCookingTime", d.formattedCookingTime}, {"cookingTime", d.cookingTime}, {"ingredients", d.ingredients}, {"recipe", d.recipe}};
    }

    void from_json(const json& j, Dish& d) {
        j.at("name").get_to(d.name);
        j.at("type").get_to(d.type);
        j.at("formattedCookingTime").get_to(d.formattedCookingTime);
        j.at("cookingTime").get_to(d.cookingTime);
        j.at("ingredients").get_to(d.ingredients);
        j.at("recipe").get_to(d.recipe);
    }
}


/**
 * @brief Converts a JSON object to a Dish object.
 *
 * @param j JSON object to convert.
 * @param d Dish object to hold the result.
 */
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


/**
 * @brief Constructor for the CookBook class.
 *
 * @param filename Path to the cookbook file.
 */
bool isNotSpace(unsigned char ch) {
    return !std::isspace(ch);
}


/**
 * @brief Prints the recipe for a dish.
 *
 * @param dish Dish object to print the recipe for.
 */
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

        std::cout << trimmedStep << std::endl;
    }
    std::cout << std::endl;
}


/**
 * @brief Prints a dish.
 *
 * @param dish Dish object to print.
 */
void CookBook::printDish(const Dish &dish) {
    bool last = false;
    std::cout << dish.name << SEMI_COLUMN << dish.type << SEMI_COLUMN << dish.formattedCookingTime << INGREDIENTS_EOL;
    for (const auto &ingredient: dish.ingredients) {
        if (ingredient == dish.ingredients.back()) {
            last = true;
        }
        std::cout << TAB << ingredient << (last ? EMPTY : COMMA_EOL);
    }
    std::cout << EOL;
}


/**
 * @brief Finds dishes that match the input ingredients.
 *
 * @param inputIngredients Ingredients to match.
 * @param matchedDishes Vector to hold the matched dishes.
 */
void CookBook::findMatchingDishes(const std::vector<std::string> &inputIngredients, std::vector<Dish> &matchedDishes) {
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
}


/**
 * @brief Loads dishes from the cookbook.
 *
 * @param matchedDishes Vector of matched dishes.
 * @param start Start index.
 * @param end End index.
 */
void CookBook::loadDishes(std::vector<Dish> &matchedDishes, int start, int end) {
    while (true) {
        for (int i = start; i < end; ++i) {
            std::cout << std::to_string(i + 1) + DOT;
            printDish(matchedDishes[i]);
        }

        std::cout << ENTER_NUM_OF_DISH;
        std::string input;
        std::cin >> input;

        if (input == MORE) {
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
}


/**
 * @brief Suggests a dish based on the input ingredients.
 *
 * @param inputIngredients Ingredients to match.
 * @return True if a dish was suggested, false otherwise.
 */
bool CookBook::suggestDish(const std::vector<std::string> &inputIngredients) {
    std::vector<Dish> matchedDishes;

    findMatchingDishes(inputIngredients, matchedDishes);

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

    loadDishes(matchedDishes, start, end);

    return true;
}


/**
 * @brief Sorts dishes based on the sorting method.
 *
 * @param method Sorting method.
 * @param dishes Vector of dishes to sort.
 */
void CookBook::sortDishes(const std::string& method, std::vector<Dish>& dishes) {
    if (method == TYPE) {
        std::sort(dishes.begin(), dishes.end(), [](const Dish& a, const Dish& b) {
            return a.type < b.type;
        });
    } else if (method == TIME) {
        std::sort(dishes.begin(), dishes.end(), [](const Dish& a, const Dish& b) {
            return a.cookingTime < b.cookingTime;
        });
    } else if (method == ALPHABET) {
        std::sort(dishes.begin(), dishes.end(), [](const Dish& a, const Dish& b) {
            return a.name < b.name;
        });
    }
}


/**
 * @brief Parses a dish from the cookbook.
 *
 * @param dishBuffer Buffer to hold the dish.
 * @return Parsed dish.
 */
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
            parseRecipe(dishBuffer, dish);
        } else {
            parseLine(dishLine, dish, dishBuffer);
        }
    }
    return dish;
}


/**
 * @brief Matches the input ingredients with the dish ingredients.
 *
 * @param inputIngredients Ingredients to match.
 * @param dishIngredients Ingredients of the dish.
 * @return True if the dish matches, false otherwise.
 */
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


/**
 * @brief Parses the name of the dish.
 *
 * @param line Line to parse.
 * @param dish Dish object to hold the name.
 * @return Parsed name.
 */
std::string CookBook::parseName(const std::string &line, Dish &dish) {
    dish.name = line.substr(line.find(COLUMN) + 2);
    dish.name = dish.name.substr(1, dish.name.size() - 3);

    return dish.name;
}


/**
 * @brief Parses the type of the dish.
 *
 * @param line Line to parse.
 * @param dish Dish object to hold the type.
 * @return Parsed type.
 */
std::string CookBook::parseType(const std::string &line, Dish &dish) {
    dish.type = line.substr(line.find(COLUMN) + 2);
    dish.type = dish.type.substr(1, dish.type.size() - 2);

    return dish.type;
}


/**
 * @brief Parses the cooking time of the dish.
 *
 * @param line Line to parse.
 * @param dish Dish object to hold the cooking time.
 * @return Parsed cooking time.
 */
int CookBook::parseCookingTime(const std::string &line, Dish &dish) {
    std::string cookingTime = line.substr(line.find(COLUMN) + 2);
    cookingTime = cookingTime.substr(0, cookingTime.size() - 1);

    int totalMinutes = std::stoi(cookingTime);

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


/**
 * @brief Parses the ingredients of the dish.
 *
 * @param dishBuffer Buffer to hold the dish.
 * @param dish Dish object to hold the ingredients.
 * @return Parsed ingredients.
 */
std::vector<std::string> CookBook::parseIngredients(std::vector<std::string> &dishBuffer, Dish &dish) {
    std::string line = dishBuffer.front();
    dishBuffer.erase(dishBuffer.begin());

    while (line.find(CLOSED_SQUARE_BRACKET) == std::string::npos) {
        std::string ingredient = line.substr(line.find(QUOTE) + 1);
        ingredient = ingredient.substr(0, ingredient.rfind(QUOTE));
        dish.ingredients.push_back(ingredient);

        line = dishBuffer.front();
        dishBuffer.erase(dishBuffer.begin());
    }

    return dish.ingredients;
}


/**
 * @brief Parses the recipe of the dish.
 *
 * @param dishBuffer Buffer to hold the dish.
 * @param dish Dish object to hold the recipe.
 * @return Parsed recipe.
 */
std::vector<std::string> CookBook::parseRecipe(std::vector<std::string> &dishBuffer, Dish &dish) {
    std::string line = dishBuffer.front();
    dishBuffer.erase(dishBuffer.begin());

    while (line.find(CLOSED_SQUARE_BRACKET) == std::string::npos) {
        std::string step = line.substr(line.find(QUOTE) + 1);
        step = step.substr(0, step.rfind(QUOTE));
        dish.recipe.push_back(step);

        line = dishBuffer.front();
        dishBuffer.erase(dishBuffer.begin());
    }

    return dish.recipe;
}


/**
 * @brief Parses a line of the dish.
 *
 * @param line Line to parse.
 * @param dish Dish object to hold the parsed data.
 * @param dishBuffer Buffer to hold the dish.
 */
void CookBook::parseLine(const std::string &line, Dish &dish, std::vector<std::string> &dishBuffer) {
    if (line.find(NAME_OF_DISH) != std::string::npos) {
        dish.name = parseName(line, dish);
    } else if (line.find(TYPE) != std::string::npos) {
        dish.type = parseType(line, dish);
    } else if (line.find(COOKING_TIME) != std::string::npos) {
        dish.cookingTime = parseCookingTime(line, dish);
    } else if (line.find(INGREDIENTS) != std::string::npos) {
        dish.ingredients = parseIngredients(dishBuffer, dish);
    } else if (line.find(RECIPE) != std::string::npos) {
        dish.recipe = parseRecipe(dishBuffer, dish);
    }
}


/**
 * @brief Loads the cookbook from a JSON file.
 *
 * @return JSON object representing the cookbook.
 */
nlohmann::json CookBook::loadJson() {
    std::ifstream inputFile(COOKBOOK_DB);
    nlohmann::json j;
    inputFile >> j;
    inputFile.close();

    return j;
}


/**
 * @brief Writes a JSON object to a file.
 *
 * @param j JSON object to write.
 */
void CookBook::writeJsonObject(const nlohmann::json& j) {
    std::ofstream outputFile(COOKBOOK_DB);
    outputFile << j.dump(4);
    outputFile.close();
}


/**
 * @brief Adds a dish to the cookbook.
 *
 * @param newDish Dish object to add.
 */
void CookBook::addDish(const Dish &newDish) {
    nlohmann::json j = loadJson();

    nlohmann::json newDishJson = {
            {"name_of_dish", newDish.name},
            {"type", newDish.type},
            {"cooking_time", newDish.cookingTime},
            {"ingredients", newDish.ingredients},
            {"recipe", newDish.recipe}
    };

    j.push_back(newDishJson);

    writeJsonObject(j);
}


/**
 * @brief Deletes a dish from the cookbook.
 *
 * @param dishName Name of the dish to delete.
 */
void CookBook::deleteDish(const std::string& dishName) {
    nlohmann::json j = loadJson();

    for (auto it = j.begin(); it != j.end(); ++it) {
        if ((*it)["name_of_dish"] == dishName) {
            j.erase(it);
            break;
        }
    }

    writeJsonObject(j);
}


/**
 * @brief Edits a dish in the cookbook.
 *
 * @param dishName Name of the dish to edit.
 * @param updatedDish Updated dish object.
 */
void CookBook::editDish(const std::string& dishName, const Dish& updatedDish) {
    nlohmann::json j = loadJson();

    for (auto& dish : j) {
        if (dish["name_of_dish"] == dishName) {
            dish["name_of_dish"] = updatedDish.name;
            dish["type"] = updatedDish.type;
            dish["cooking_time"] = updatedDish.cookingTime;
            dish["ingredients"] = updatedDish.ingredients;
            dish["recipe"] = updatedDish.recipe;
            break;
        }
    }

    writeJsonObject(j);
}


/**
 * @brief Prints an array of strings.
 *
 * @param array Array to print.
 * @param label Label for the array.
 */
void CookBook::printArray(const nlohmann::json &array, const std::string &label) {
    bool lastElement = false;
    std::cout << label << COLUMN_EOL;
    for (const auto &element: array) {
        if (element == array.back()) {
            lastElement = true;
        }
        std::cout << TAB << element;
        std::cout << (lastElement ? "" : COMMA_EOL);
    }
    std::cout << EOL;
}


/**
 * @brief Views a dish from the cookbook.
 *
 * @param name Name of the dish to view.
 */
void CookBook::viewDish(const std::string &name) {
    nlohmann::json j = loadJson();

    for (const auto &dish : j) {
        if (dish["name_of_dish"] == name) {
            std::cout << dish["name_of_dish"] << SEMI_COLUMN << std::endl;
            std::cout<< dish["type"] << SEMI_COLUMN << std::endl;
            std::cout << dish["cooking_time"] << SEMI_COLUMN << std::endl;
            printArray(dish["ingredients"], "Ingredients");
            printArray(dish["recipe"], "Recipe");
            std::cout << EOL;
            return;
        }
    }

    // If the dish was not found
    std::cout << "Dish not found." << std::endl;
}