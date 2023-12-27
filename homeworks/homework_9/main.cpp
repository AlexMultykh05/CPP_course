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

    db.push_back(shared_ptr<Title>(title));

    db_query_5(db_index, "The Shawshank Redemption");
    db_query_6(index_years, 1994);
    db_query_7(index_years, 1994, 1995);
    db_query_8(index_actors, Actor("Tim", "Robbins", 1958));
    for (auto &&title: db_query_9(db, Actor("Tim", "Robbins", 1958))) {
        cout << title->name() << endl;
    }
    cout << endl;
    cout << endl;
    for (auto &&title: db_query_10(db, "Drama")) {
        cout << title->name() << endl;
    }
    cout << endl;
    cout << endl;
    cout << db_query_11(db, Type::MOVIE, "Drama");
    cout << endl;
    cout << endl;
    cout << db_query_12(db, "Drama");
    cout << endl;
    cout << endl;

    title->print_json(cout);
}