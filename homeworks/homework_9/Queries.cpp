#include "Queries.h"

using namespace std;

bool operator==(const Actor &actor_1, const Actor &actor_2) {
    return actor_1.name() == actor_2.name() && actor_1.surname() == actor_2.surname() &&
           actor_1.year() == actor_2.year();
}

class Predicate_Actor {
private:
    Actor actor_;
public:
    Predicate_Actor(const Actor &actor) : actor_(actor) {};

    bool operator()(const shared_ptr<Title> &title_ptr) {
        return title_ptr->actors().count(actor_) != 1;
    }
};

class Comparator_Years_Name {
public:
    bool operator()(const shared_ptr<Title> &title_ptr_1, const shared_ptr<Title> &title_ptr_2) {
        if (title_ptr_1->year() == title_ptr_2->year()) {
            return title_ptr_1->name() > title_ptr_2->name();
        }
        return title_ptr_1->year() < title_ptr_2->year();
    }
};

class Rating_Calculator {
private:
    Type type_;
    string genre_;
    int sum_;
    int cnt_;
public:
    Rating_Calculator(Type type, const std::string &genre) : type_(type), genre_(genre), sum_(0), cnt_(0) {}

    bool operator()(const shared_ptr<Title> &title_ptr) {
        bool check = true;
        if (title_ptr->type() == type_ && title_ptr->genre() == genre_) {
            sum_ += title_ptr->rating();
            cnt_++;
        } else {
            check = false;
        }

        return check;
    }

    int avg() const {
        return (cnt_ == 0) ? 0 : sum_ / cnt_;
    }
};


void db_query_1(const vector<shared_ptr<Title>> &db, ostream &stream) {
    for (const shared_ptr<Title> &title: db) {
        title->print_json(stream);
        stream << endl;
    }
}

void db_query_2(const vector<shared_ptr<Title>> &db, ostream &stream) {
    for (auto &movie: db) {
        if (movie->genre() == "comedy" && movie->year() < 2010 &&
            (movie->actors().count(Actor{"Ivan", "Trojan", 1964}) > 0 ||
             movie->actors().count(Actor{"Tereza", "Voriskova", 1989}) > 0)) {
            stream << movie->name() << endl;
        }
    }
}

void db_query_3(const vector<shared_ptr<Title>> &db, unsigned short seasons, unsigned short episodes, ostream &stream) {
    for (const shared_ptr<Title> &title: db) {
        if (title->type() == Type::SERIES) {
            if (dynamic_cast<Series *>(&*title)->seasons() >= seasons ||
                dynamic_cast<Series *>(&*title)->episodes() >= episodes) {
                title->print_json(stream);
                stream << endl;
            }
        }
    }
}

void db_query_4(const vector<shared_ptr<Title>> &db, const type_info &type, unsigned short start, unsigned short end,
                ostream &stream) {
    for (const shared_ptr<Title> &title: db) {
        if (typeid(*title) == type) {
            if (title->year() >= start && title->year() < end)
                stream << title->name() << endl;

        }
    }
}

void db_index_titles(const vector<shared_ptr<Title>> &db, map<string, shared_ptr<Title>> &index) {
    for (auto &&title_ptr: db) {
        index.emplace(title_ptr->name(), title_ptr);
    }
}

void db_query_5(const map<string, shared_ptr<Title>> &index, const string &name, ostream &stream) {
    auto it = index.find(name);
    stream << "\"" << name << "\" -> ";
    if (it == index.end()) {
        stream << "Not found!" << endl;
        return;
    }
    it->second->print_json(stream);
}

void db_index_years(const vector<shared_ptr<Title>> &db,
                    multimap<unsigned short, shared_ptr<Title>> &index) {
    for (auto &&title: db) {
        index.emplace(title->year(), title);
    }
}

void db_query_6(const multimap<unsigned short, shared_ptr<Title>> &index, unsigned short year, ostream &stream) {
    auto it_pair = index.equal_range(year);
    if (it_pair.first == it_pair.second) {
        stream << year << " -> " << "Not found!" << endl;
        return;
    }
    for (auto it = it_pair.first; it != it_pair.second; ++it) {
        stream << it->first << " -> \"" << it->second->name() << "\"" << endl;
    }
}

void
db_query_7(const multimap<unsigned short, shared_ptr<Title>> &index, unsigned short begin, unsigned short end,
           ostream &stream) {
    auto it_begin = index.lower_bound(begin);
    auto it_end = index.lower_bound(end);
    if (it_begin == it_end) {
        stream << '[' << begin << ", " << end << ')' << " -> " << "Not found!" << endl;
        return;
    }
    for (auto it = it_begin; it != it_end; ++it) {
        stream << it->first << " -> \"" << it->second->name() << "\"" << endl;
    }
}

void db_index_actors(const vector<shared_ptr<Title>> &db,
                     unordered_multimap<Actor, shared_ptr<Title>> &index) {
    for (auto &&title: db) {
        for (auto &&actor: title->actors()) {
            index.emplace(actor, title);
        }
    }
}

vector<Title *> db_query_8(const unordered_multimap<Actor, shared_ptr<Title>> &index, const Actor &actor) {
    vector<Title *> result;
    for (const auto &[key, value]: index) {
        if (key == actor) {
            result.push_back(&*value);
        }
    }
    return result;
}

vector<shared_ptr<Title>> db_query_9(const vector<shared_ptr<Title>> &db, const Actor &actor) {
    vector<shared_ptr<Title>> result;

    result.resize(db.size());

    copy(db.begin(), db.end(), result.begin());

    auto it = remove_if(result.begin(), result.end(), Predicate_Actor(actor));

    result.resize(distance(result.begin(), it));

    result.erase(it, result.end());

    sort(result.rbegin(), result.rend(), Comparator_Years_Name());

    return result;
}

vector<shared_ptr<Title>> db_query_10(const vector<shared_ptr<Title>> &db, const string &genre) {
    vector<shared_ptr<Title>> result;

    result.resize(db.size());

    auto it = copy_if(db.begin(), db.end(), result.begin(), [genre](const shared_ptr<Title> &title_ptr) {
        return title_ptr->genre() == genre;
    });

    result.erase(it, result.end());

    sort(result.begin(), result.end(), [](const shared_ptr<Title> &title_ptr_1, const shared_ptr<Title> &title_ptr_2) {
        return title_ptr_1->name() < title_ptr_2->name();
    });
    return result;
}

int db_query_11(const vector<shared_ptr<Title>> &db, Type type, const string &genre) {
    Rating_Calculator rating_calculator(type, genre);

    rating_calculator = for_each(db.begin(), db.end(), rating_calculator);

    return rating_calculator.avg();
}

int db_query_12(const vector<shared_ptr<Title>> &db, const string &genre) {
    int num_of_titles = 0;
    for_each(db.begin(), db.end(), [genre, &num_of_titles](const shared_ptr<Title> &title_ptr) {
        if (title_ptr->genre() == genre) {
            num_of_titles++;
        }
    });
    return num_of_titles;
}