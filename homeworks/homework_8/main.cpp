#include <string>
#include <vector>
#include <sstream>
#include "Title.h"
#include "Queries.h"

using namespace std;

int main() {
    vector<shared_ptr<Title>> db;
    map<string, shared_ptr<Title>> db_index;
    multimap<unsigned short, shared_ptr<Title>, less<unsigned short>> index_years;
    unordered_multimap<Actor, shared_ptr<Title>> index_actors;
    db_index_titles(db, db_index);
    db_index_years(db, index_years);
    db_index_actors(db, index_actors);

    Title *title = new Movie("The Shawshank Redemption", 1994, "Drama", 9, {Actor("d", "f", 1974), Actor("a", "b", 1983)}, 142);

    title->print_json(cout);
}