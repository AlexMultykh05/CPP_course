#include "Title.h"
#include "Actor.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

Type Movie::type() const {
    return Type::MOVIE;
}

Type Series::type() const {
    return Type::SERIES;
}

Title::Title(const std::string &name, unsigned short year, const std::string &genre, unsigned short rating, const std::set<Actor> &actors) : name_(name), year_(year), genre_(genre), rating_(rating), actors_(actors) {}

Movie::Movie(const string& name, unsigned short year, const string& genre, unsigned short rating, const set<Actor>& actors, unsigned short length):
        Title(name, year, genre, rating, actors), length_(length) {}

Movie::Movie(string&&name, unsigned short year, string&& genre, unsigned short rating, set<Actor>&& actors, unsigned short length):
        Title(std::move(name), year, std::move(genre), rating, std::move(actors)), length_(length) {}

Series::Series(const string& name, unsigned short year, const string& genre, unsigned short rating, const set<Actor>& actors, unsigned short seasons, unsigned short episodes):
        Title(name, year, genre, rating, actors), seasons_(seasons), episodes_(episodes) {}

Series::Series(string&& name, unsigned short year, string&& genre, unsigned short rating, set<Actor>&& actors, unsigned short seasons, unsigned short episodes):
        Title(std::move(name), year, std::move(genre), rating, std::move(actors)), seasons_(seasons), episodes_(episodes) {}

//
//void Movie::print_json(std::ostream &os) const {
//    os << ", length:" << length_;
//}
//
//void Series::print_json(std::ostream &os) const {
//    os << ", seasons:" << seasons_ << ", episodes:" << episodes_;
//}


void Title::print_json(ostream &os) const {
    if (type() == Type::MOVIE) {
        os << "{ type: " << "\"MOVIE\", ";
    } else if (type() == Type::SERIES) {
        os << "{ type: " << "\"SERIES\", ";
    }

    os << "name: \"" << name_ << "\", "
       << "year: " << year_ << ", "
       << "genre: \"" << genre_ << "\", "
       << "rating: " << rating_ << ", ";

    if (!actors_.empty()) {
        os << "actors: [ ";

        for (auto it = actors_.begin(); it != actors_.end(); ++it) {
            if (it != actors_.begin() && it != actors_.end()) {
                os << ", ";
            }
            os << *it;
        }
        os << " ], ";
    }
    if (type() == Type::MOVIE){
        os << "length: " << static_cast<const Movie*>(this) -> length();
    } else if (type() == Type::SERIES){
        os << "seasons: " << static_cast<const Series*>(this) -> seasons() << ", episodes: " << static_cast<const Series*>(this) -> episodes();
    }

    os << " }";
}

