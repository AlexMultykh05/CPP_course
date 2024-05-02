//
// Created by Alex Multykh on 28.04.2024.
//

#ifndef PROJECT_COOKBOOK_HPP
#define PROJECT_COOKBOOK_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class CookBook {
private:
    std::string name_;
    std::string type_;
    unsigned short time_;
    std::vector<std::string> ingredients_;
    std::vector<std::string> recipe_;

public:
    CookBook(const std::string& filename);

    const std::string &name() const;

    const std::string &type() const;

    unsigned short time() const;

    const std::vector<std::string> &ingredients() const;

    const std::vector<std::string> &recipe() const;

    void suggest_dishes(std::ostream &os = std::cout) const;

    static void print_recipes(const std::vector<CookBook> &books, std::ostream &os = std::cout);

    static void read_json(std::vector<CookBook> &books, std::istream &is);

};


inline const std::string &CookBook::name() const {
    return name_;
}

inline const std::string &CookBook::type() const {
    return type_;
}

inline unsigned short CookBook::time() const {
    return time_;
}

inline const std::vector<std::string> &CookBook::ingredients() const {
    return ingredients_;
}

inline const std::vector<std::string> &CookBook::recipe() const {
    return recipe_;
}


#endif //PROJECT_COOKBOOK_HPP
