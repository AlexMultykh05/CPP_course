#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Movie.h"
#include "Database.h"

using namespace std;

void Database::import(const string &filename, vector<Movie> &db) {
    ifstream fileIn;

    fileIn.open(filename);

    if (!fileIn.good()) {
        throw Exception{1, "Unable to open input file <" + filename + ">"};
    }

    import(fileIn, db);
}

void Database::import(istream &stream, vector<Movie> &db) {
    string line;
    int numOfLine = 0;
    while (getline(stream, line)) {
        numOfLine++;
        if (line.empty()) {
            continue;
        }
        db.push_back(parseAll(line, numOfLine));
    }

}

void Database::exceptionHandler(const std::string &field, int &numOfLine, istream &ss, string &line) {
    if (!getline(ss, line, ';'))
        throw Exception{2, "Missing field <" + field + "> on line <" + to_string(numOfLine) + ">"};
}

Movie Database::parseAll(const std::string &line, int numOfLine) {
    istringstream ss(line);
    string genre;
    string name;
    unsigned short year;
    unsigned short rating;
    set<string> actors;
    string field;

    exceptionHandler("name", numOfLine, ss, field);

    name = parseStr("name", field, numOfLine);

    exceptionHandler("year", numOfLine, ss, field);

    year = parseInt("year", field, numOfLine, 1900, 2100);

    exceptionHandler("genre", numOfLine, ss, field);

    genre = parseStr("genre", field, numOfLine);

    exceptionHandler("rating", numOfLine, ss, field);

    rating = parseInt("rating", field, numOfLine, 0, 100);

    getline(ss, field, ';');

    actors = parseSet(field);

    return {name, year, genre, rating, actors};

}

unsigned short Database::parseInt(const std::string &name, const std::string &field, int numOfLine, int min,
                                  int max) {
    try {
        size_t position;
        int num = stoi(field, &position);
        if (num < min || num > max) {
            throw Exception{2, "Integer out of range <" + to_string(min) + ", " + to_string(max) + "> in field <"
                               + name + "> on line <" + to_string(numOfLine) + ">"};
        }

        if (position != field.size()) {
            throw Exception{2, "Malformed integer in field <" + name + "> on line <" + to_string(numOfLine) + ">"};
        }

        return static_cast<unsigned short>(num);
    }
    catch (const out_of_range &) {
        throw Exception{2, "Overflow integer in field <" + name + "> on line <" + to_string(numOfLine) + ">"};
    }
    catch (const invalid_argument &) {
        throw Exception{2, "Invalid integer in field <" + name + "> on line <" + to_string(numOfLine) + ">"};
    }

}

string Database::parseStr(const std::string &name, const std::string &field, int numOfLine) {
    if (!field.empty())
        return field;
    else
        throw Exception{2, "Empty string in field <" + name + "> on line <" + to_string(numOfLine) + ">"};
}

set<string> Database::parseSet(const std::string &field) {
    set<string> setOfActors;
    string word;
    stringstream ss(field);
    while (getline(ss, word, ',')) {
        setOfActors.insert(word);
    }
    return setOfActors;
}
