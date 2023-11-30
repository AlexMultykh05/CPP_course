#include "Queries.h"

using namespace std;

bool operator==(const Actor &actor1, const Actor &actor2) {
    return actor1.name() == actor2.name() && actor1.surname() == actor2.surname() && actor1.year() == actor2.year();
}

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
        pair<string, shared_ptr<Title>> item(title_ptr->name(), title_ptr);
        index.insert(std::move(item));
        index.insert(std::make_pair(title_ptr->name(), title_ptr));
        index.emplace(title_ptr->name(), title_ptr);
    }
}

void db_query_5(const map<string, shared_ptr<Title>> &index, const string &name, ostream &stream) {
    auto it = index.find(name);
    if (it == index.end()) {
        stream << "Not found" << endl;
        return;
    }
    it->second->print_json(stream);
    stream << endl;
}

void db_index_years(const vector<shared_ptr<Title>> &db, multimap<unsigned short, shared_ptr<Title>> &index) {
    for (auto &&title_ptr: db) {
        pair<unsigned short, shared_ptr<Title>> item(title_ptr->year(), title_ptr);
        index.insert(std::move(item));
        index.insert(std::make_pair(title_ptr->year(), title_ptr));
        index.emplace(title_ptr->year(), title_ptr);
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

void db_query_7(const multimap<unsigned short, shared_ptr<Title>> &index, unsigned short begin, unsigned short end, ostream &stream) {
    auto it_pair = index.lower_bound(begin);
    if (it_pair == index.end()) {
        stream << begin << " -> " << "Not found!" << endl;
        return;
    }
    for (auto it = it_pair; it != index.end(); ++it) {
        if (it->first >= end) {
            break;
        }
        stream << it->first << " -> \"" << it->second->name() << "\"" << endl;
    }
}

void db_index_actors(const vector<shared_ptr<Title>> &db, unordered_multimap<Actor, shared_ptr<Title>> &index) {
    for (auto &&title_ptr: db) {
        for (auto &&actor: title_ptr->actors()) {
            pair<Actor, shared_ptr<Title>> item(actor, title_ptr);
            index.insert(std::move(item));
            index.insert(std::make_pair(actor, title_ptr));
            index.emplace(actor, title_ptr);
        }
    }
}

vector<Title *> db_query_8(const unordered_multimap<Actor, shared_ptr<Title>> &index, const Actor &actor) {
    vector<Title *> result;
    auto it_pair = index.equal_range(actor);
    if (it_pair.first == it_pair.second) {
        return result;
    }
    for (auto it = it_pair.first; it != it_pair.second; ++it) {
        result.push_back(it->second.get());
    }
    return result;

    //TODO check if it works
}

vector<shared_ptr<Title>> db_query_9(const vector<shared_ptr<Title>> &db, const Actor &actor) {
    vector<shared_ptr<Title>> result;
    for (auto &&title_ptr: db) {
        if (title_ptr->actors().count(actor) > 0) {
            result.push_back(title_ptr);
        }
    }
    return result;
}

class Predicate_Actor {
private:
    Actor actor_;
public:
    Predicate_Actor(const Actor &actor) : actor_(actor) {};

    bool operator()(const std::shared_ptr<Title> &title_ptr) {
        return title_ptr->actors().count(actor_) != 1;
    }

//    void earase(begin, end)
};

