#include <iostream>
#include "CookBook.hpp"

int main() {
    std::vector<std::string> inputIngredients;
    std::string ingredient;

    std::cout << "Enter 3 main ingredients: ";
    for (int i = 0; i < 3; i++) {
        std::cin >> ingredient;
        inputIngredients.push_back(ingredient);
    }

    CookBook myCookBook("/Users/alexmultykh/Desktop/multykho/project/src/cookbook_db.json");

    myCookBook.printDish(inputIngredients);

    return 0;
}