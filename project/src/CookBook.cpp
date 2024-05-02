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

}


void CookBook::suggest_dishes(std::ostream &os) const {

}


void CookBook::print_recipes(const std::vector<CookBook> &books, std::ostream &os) {

}


void CookBook::read_json(std::vector<CookBook> &books, std::istream &is) {
    std::string name, type;
    unsigned short time;
    std::vector<std::string> ingredients, recipes;

    while (is >> name >> type >> time) {
        std::string ingredient;
        while (is >> ingredient) {
            ingredients.push_back(ingredient);
        }

        std::string recipe;
        while (is >> recipe) {
            recipes.push_back(recipe);
        }

        books.emplace_back(name, type, time, ingredients, recipes);
    }
}