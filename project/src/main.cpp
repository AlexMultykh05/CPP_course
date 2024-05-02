#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

class CookBook {
public:
    // Constructor
    CookBook(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file." << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        content_ = buffer.str();
    }

    // Function to print recipes

    void printRecipes() const {
        std::istringstream f(content_);
        std::string line;
        int recipeNumber = 1;

        while (std::getline(f, line)) {
            if (line.find("name_of_dish") != std::string::npos) {
                std::string dishName = line.substr(line.find(": ") + 2);
                dishName = dishName.substr(1, dishName.size() - 3);
                std::cout << recipeNumber++ << ". " << dishName << "; ";
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
    }

private:
    std::string content_;
};

int main() {
    CookBook myCookBook("/Users/alexmultykh/Desktop/multykho/project/src/cookbook_db.json");
    myCookBook.printRecipes();

    return 0;
}
