#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "Title.h"
#include "Database.h"

using namespace std;

void Database::import(const string &filename, vector<shared_ptr<Title>> &db) {
    ifstream fileIn;

    fileIn.open(filename);

    if (!fileIn.good()) {
        throw Exception{ERROR_NO_FILE, "Unable to open input file <" + filename + ">"};
    }

    import(fileIn, db);
}

void Database::import(istream &stream, vector<shared_ptr<Title>> &db) {
    string line;
    int numOfLine = 0;
    while (getline(stream, line)) {
        numOfLine++;
        if (line.empty()) {
            continue;
        }
        parseAll(line, numOfLine, db);
    }
}

void Database::parseAll(const std::string &line, int numOfLine, vector<shared_ptr<Title>> &db) {
    istringstream ss(line);
    string type, genre, name, field;
    unsigned short year, rating;
    set<Actor> actors;

    type = parseStr(TYPE, field, numOfLine, ss,field);

    name = parseStr(NAME, field, numOfLine, ss,field);

    year = parseInt(YEAR, field, numOfLine, MIN_FILM_YEAR, MAX_FILM_YEAR, ss, field);

    genre = parseStr(GENRE, field, numOfLine, ss,field);

    rating = parseInt(RATING, field, numOfLine, MIN_RATING, MAX_RATING, ss, field);

    getline(ss, field, ';');

    actors = parseSet(field, numOfLine);

    if (type == MOVIE){
        unsigned short length = parseInt(LENGTH, field, numOfLine, MIN_LENGTH, MAX_LENGTH, ss, field);

        db.push_back(make_shared<Movie>(name, year, genre, rating, actors, length));
    } else if (type == SERIES) {
        unsigned short seasons = parseInt(SEASONS, field, numOfLine, MIN_SEASONS, MAX_SEASONS, ss, field);
        unsigned short episodes = parseInt(EPISODES, field, numOfLine, MIN_EPISODES, MAX_EPISODES, ss, field);

        db.push_back(make_shared<Series>(name, year, genre, rating, actors, seasons, episodes));
    } else {
         Exception{ERROR_NO_FIELD,
                        "Invalid type selector in field <type> on line <" + to_string(numOfLine) + ">"};
    }
}


unsigned short Database::parseInt(const std::string &name, const std::string &field, int numOfLine, int min,
                                  int max, istream &ss, string &line) {
    if (!getline(ss, line, ';')){
        throw Exception{ERROR_NO_FIELD, "Missing field <" + name + "> on line <" + to_string(numOfLine) + ">"};
    }
    try {
        size_t position;
        int num = stoi(field, &position);
        if (num < min || num > max) {
            throw Exception{ERROR_NO_FIELD, "Integer out of range <" + to_string(min) + ", " + to_string(max) + "> in field <"
                               + name + "> on line <" + to_string(numOfLine) + ">"};
        }

        if (position != field.size()) {
            throw Exception{ERROR_NO_FIELD, "Malformed integer in field <" + name + "> on line <" + to_string(numOfLine) + ">"};
        }

        return static_cast<unsigned short>(num);
    }
    catch (const out_of_range &) {
        throw Exception{ERROR_NO_FIELD, "Overflow integer in field <" + name + "> on line <" + to_string(numOfLine) + ">"};
    }
    catch (const invalid_argument &) {
        throw Exception{ERROR_NO_FIELD, "Invalid integer in field <" + name + "> on line <" + to_string(numOfLine) + ">"};
    }
}

string Database::parseStr(const std::string &name, const std::string &field, int numOfLine, istream &ss, string &line) {
    if (!getline(ss, line, ';'))
        throw Exception{ERROR_NO_FIELD, "Missing field <" + name + "> on line <" + to_string(numOfLine) + ">"};

    if (!field.empty())
        return field;
    else
        throw Exception{ERROR_NO_FIELD, "Empty string in field <" + name + "> on line <" + to_string(numOfLine) + ">"};
}

set<Actor> Database::parseSet(const std::string& field, int numOfLine) {
    set<Actor> setOfActors;
    string actor;
    stringstream ss(field);

    while (getline(ss, actor, ',')) {
        stringstream ssActor(actor);
        Actor act;
        try {
            ssActor >> act;
        } catch (Exception &e) {
            e.code = ERROR_NO_FIELD;
            e.text += "<" + actor + "> on line <" + to_string(numOfLine) + ">";
            throw e;
        }
        setOfActors.insert(act);
    }
    return setOfActors;
}
