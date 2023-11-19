#include <iostream>
#include <vector>
#include "Queries.h"
#include "Movie.h"

using namespace std;

void db_query_1(const vector<Movie>& db, ostream& stream) {
    for (const Movie& movie : db) {
        movie.print_json(stream);
        stream << endl;
    }
}

void db_query_2(const vector<Movie>& db, ostream& stream) {
    for (const Movie& movie : db) {
        if (movie.genre() == "comedy" && movie.year() < 2010 && (movie.actors().count("Ivan Trojan") > 0 || movie.actors().count("Tereza Voriskova"))) {
            stream << movie.name() << endl;
        }
    }
}