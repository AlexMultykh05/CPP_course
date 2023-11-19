#include "Movie.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

Movie::Movie(const string& name, unsigned short year, const string& genre, unsigned short rating, const set<string>& actors):
    name_(name), year_(year), genre_(genre), rating_(rating), actors_(actors) {}

Movie::Movie(string&&name, unsigned short year, string&& genre, unsigned short rating, set<string>&& actors):
    name_(std::move(name)), year_(year), genre_(std::move(genre)), rating_(rating), actors_(std::move(actors)) {}

void Movie::print_json(ostream& os) const {
    os << "{ "
          "name: " << "\"" << name_ << "\", "
          "year: " << year_ << ", "
          "genre: " << "\"" << genre_ << "\", "
          "rating: " << rating_ ;
    if (actors_.empty()) {
        os << " }";
        return;
    }
    os << ", " << "actors: [ ";
    for (auto it = actors_.begin(); it != actors_.end(); ++it) {
        if (it != actors_.begin() && it != actors_.end()) {
            os << ", ";
        }
        os << "\"" << *it << "\"";
    }
    os << " ]"
          " }";

}

