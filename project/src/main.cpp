/**
 * @file main.cpp
 * @author Alex Multykh
 * @date 28.04.2024
 */


#include "CookBook.hpp"


/**
 * @brief Reads ingredients from the standard input.
 *
 * @return std::vector<std::string> Vector of ingredients.
 */
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


/**
 * @brief Prints all dishes from the cookbook.
 *
 * @param cookbook JSON object representing the cookbook.
 */
void printAllDishes(const nlohmann::json& cookbook) {
    int dishNum = 1;
    std::cout << EOL << "The cookbook contains the following dishes:" << std::endl;
    for (const auto& dish : cookbook) {
        std::cout << std::to_string(dishNum) + DOT << dish[NAME_OF_DISH] << '\n';
        dishNum++;
    }
    std::cout << std::endl;
}


/**
 * @brief Checks if the cookbook is empty or not found.
 */
void checkIfEmptyCookBook() {
    std::ifstream file(COOKBOOK_DB);
    if (!file || file.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "The cookbook is empty or not found. Nothing to delete.\n";
        return;
    }
}


/**
 * @brief Handles the recipe searching process.
 *
 * @param myCookBook Reference to the CookBook object.
 */
void recipeSearching(CookBook& myCookBook) {
    std::cout << ENTER_INGREDIENTS;

    std::vector<std::string> inputIngredients = readIngredients();
    while (true) {
        bool dishesSuggested = myCookBook.suggestDish(inputIngredients);

        if (!dishesSuggested) {
            std::cout << "Enter 'end' to return to the main menu or 'add' to add more ingredients: ";
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
}


/**
 * @brief Handles the dish creation process.
 *
 * @param myCookBook Reference to the CookBook object.
 */
void createDish(CookBook& myCookBook) {
    Dish newDish;
    std::cout << "Enter the name of the new dish: ";
    std::getline(std::cin, newDish.name);
    std::cout << "Enter the type of the new dish: ";
    std::getline(std::cin, newDish.type);
    std::cout << "Enter the cooking time of the new dish (in minutes): ";
    std::cin >> newDish.cookingTime;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter the ingredients of the new dish (separated by comma: ";
    newDish.ingredients = readIngredients();
    std::cout << "Enter the recipe of the new dish (separated by comma: ";
    newDish.recipe = readIngredients();

    myCookBook.addDish(newDish);
}


/**
 * @brief Handles the dish reading process.
 *
 * @param myCookBook Reference to the CookBook object.
 */
void readDish(CookBook& myCookBook) {
    checkIfEmptyCookBook();


    printAllDishes(myCookBook.loadJson());

    std::string dishName;
    std::cout << "Enter the name of the dish you want to view: ";
    std::getline(std::cin, dishName);

    myCookBook.viewDish(dishName);
}


/**
 * @brief Handles the dish updating process.
 *
 * @param myCookBook Reference to the CookBook object.
 */
void updateDish(CookBook& myCookBook) {
    checkIfEmptyCookBook();

    printAllDishes(myCookBook.loadJson());

    std::string dishName;
    std::cout << "Enter the name of the dish you want to edit: ";
    std::getline(std::cin, dishName);

    Dish updatedDish;
    std::cout << "Enter the new name of the dish: ";
    std::getline(std::cin, updatedDish.name);
    std::cout << "Enter the new type of the dish: ";
    std::getline(std::cin, updatedDish.type);
    std::cout << "Enter the new cooking time of the dish (in minutes): ";
    std::cin >> updatedDish.cookingTime;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter the new ingredients of the dish (separated by comma): ";
    updatedDish.ingredients = readIngredients();
    std::cout << "Enter the new recipe of the dish (separated by comma: ";
    updatedDish.recipe = readIngredients();

    myCookBook.editDish(dishName, updatedDish);
}


/**
 * @brief Handles the dish deletion process.
 *
 * @param myCookBook Reference to the CookBook object.
 */
void deleteDish(CookBook& myCookBook) {
    checkIfEmptyCookBook();

    printAllDishes(myCookBook.loadJson());

    std::string dishName;
    std::cout << "Enter the name of the dish you want to delete: ";
    std::getline(std::cin, dishName);

    myCookBook.deleteDish(dishName);
}


/**
 * @brief Handles the cookbook editing process.
 *
 * @param myCookBook Reference to the CookBook object.
 */
void cookBookEditing(CookBook& myCookBook) {
    std::cout << "'1' to create a dish\n'2' to read a dish\n'3' to update a dish\n'4' to delete a dish\nEnter your choice:";
    int editChoice;
    std::cin >> editChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the input buffer

    switch (editChoice) {
        case 1: {
            createDish(myCookBook);
            break;
        }
        case 2: {
            readDish(myCookBook);
            break;
        }
        case 3: {
            updateDish(myCookBook);
            break;
        }
        case 4: {
            deleteDish(myCookBook);
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}


/**
 * @brief Main function.
 *
 * @return int
 */
int main() {
    CookBook myCookBook(COOKBOOK_DB);

    while (true) {
        std::cout << "'1' to look up a recipe \n'2' to edit the cookbook\n'3' to view cookbook\n'4' to exit\nEnter your choice:";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                recipeSearching(myCookBook);
                break;
            }
            case 2: {
                cookBookEditing(myCookBook);
                break;
            }
            case 3: {
                printAllDishes(myCookBook.loadJson());
                break;
            }
            case 4:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

