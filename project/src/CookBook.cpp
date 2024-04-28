//
// Created by Alex Multykh on 28.04.2024.
//

#include "CookBook.hpp"

CookBook::CookBook(const std::string &name, const std::string &type, unsigned short time,
                   const std::vector<std::string> &ingredients, const std::vector<std::string> &recipe)
        : name_(name), type_(type), time_(time), ingredients_(ingredients), recipes_(recipe) {}

CookBook::CookBook(std::string &&name, std::string &&type, unsigned short time,
                   std::vector<std::string> &&ingredients, std::vector<std::string> &&recipe){}