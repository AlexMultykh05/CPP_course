#ifndef INC_5TH_HW_DATABASE_H
#define INC_5TH_HW_DATABASE_H

#include <iostream>
#include <string>
#include <vector>
#include "Movie.h"

struct Exception{
    int code;
    std::string text;
};

class Database{
public:
    static void import(const std::string& filename, std::vector<Movie>& db);

    static void import(std::istream& stream, std::vector<Movie>& db);

private:
    static void exceptionHandler(const std::string& field, int& numOfLine, std::istream& ss, std::string& line);

    static std::string parseStr(const std::string& name, const std::string& field, int numOfLine);

    static unsigned short parseInt(const std::string& name, const std::string& field, int numOfLine, int min, int max);

    static std::set<std::string> parseSet(const std::string& field);

    static Movie parseAll(const std::string& line, int numOfLine);
};

#endif //INC_5TH_HW_DATABASE_H
