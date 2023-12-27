#ifndef INC_5TH_HW_DATABASE_H
#define INC_5TH_HW_DATABASE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Title.h"
#include "Actor.h"

const std::string TYPE = "type";
const std::string MOVIE = "MOVIE";
const std::string SERIES = "SERIES";
const std::string NAME = "name";
const std::string SURNAME = "surname";
const std::string YEAR = "year";
const std::string GENRE = "genre";
const std::string RATING = "rating";
const std::string LENGTH = "length";
const std::string SEASONS = "seasons";
const std::string EPISODES = "episodes";
constexpr int ERROR_NO_FILE = 1;
constexpr int ERROR_NO_FIELD = 2;
constexpr int MIN_FILM_YEAR = 1900;
constexpr int MAX_FILM_YEAR = 2100;
constexpr int MIN_RATING = 0;
constexpr int MAX_RATING = 100;
constexpr int MIN_LENGTH = 0;
constexpr int MAX_LENGTH = 300;
constexpr int MIN_SEASONS = 0;
constexpr int MAX_SEASONS = 100;
constexpr int MIN_EPISODES = 0;
constexpr int MAX_EPISODES = 10000;

struct Exception {
    int code;
    std::string text;
};

class Database {
public:
    static void import(const std::string &filename, std::vector<std::shared_ptr<Title>> &db);

    static void import(std::istream &stream, std::vector<std::shared_ptr<Title>> &db);

private:

    static std::string parseStr(const std::string &name, const std::string &field, int numOfLine, std::istream &ss, std::string &line);

    static unsigned short parseInt(const std::string &name, const std::string &field, int numOfLine, int min, int max, std::istream &ss,
             std::string &line);

    static std::set<Actor> parseSet(const std::string &field, int numOfLine);

    static void parseAll(const std::string &line, int numOfLine, std::vector<std::shared_ptr<Title>> &db);
};

#endif //INC_5TH_HW_DATABASE_H
