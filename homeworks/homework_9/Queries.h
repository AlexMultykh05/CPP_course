#ifndef DATABASE_QUERIES_H
#define DATABASE_QUERIES_H

#include "Title.h"
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include <unordered_map>
#include <algorithm>

void db_query_1(const std::vector<std::shared_ptr<Title>> &db,
                std::ostream &stream = std::cout);

void db_query_2(const std::vector<std::shared_ptr<Title>> &db,
                std::ostream &stream = std::cout);

void db_query_3(
        const std::vector<std::shared_ptr<Title>> &db,
        unsigned short seasons, unsigned short episodes,
        std::ostream &stream = std::cout);

void db_query_4(
        const std::vector<std::shared_ptr<Title>> &db,
        const std::type_info &type, unsigned short begin,
        unsigned short end,
        std::ostream &stream = std::cout);


void db_index_titles(
        const std::vector<std::shared_ptr<Title>> &db,
        std::map<std::string, std::shared_ptr<Title>> &index
);

void db_index_years(
        const std::vector<std::shared_ptr<Title>> &db,
        std::multimap<unsigned short, std::shared_ptr<Title>> &index
);

void db_index_actors(
        const std::vector<std::shared_ptr<Title>> &db,
        std::unordered_multimap<Actor, std::shared_ptr<Title>> &index
);

template<>
struct std::hash<Actor> {
    std::size_t operator()(const Actor &actor) const noexcept{
        return std::hash<std::string>()(actor.surname());
    }
};

void db_query_5(
        const std::map<std::string, std::shared_ptr<Title>> &index,
        const std::string &name,
        std::ostream &stream = std::cout
);

void db_query_6(
        const std::multimap<unsigned short, std::shared_ptr<Title>> &index,
        unsigned short year,
        std::ostream &stream = std::cout
);

void db_query_7(
        const std::multimap<unsigned short, std::shared_ptr<Title>> &index,
        unsigned short begin,
        unsigned short end,
        std::ostream &stream = std::cout
);

std::vector<Title *> db_query_8(
        const std::unordered_multimap<Actor, std::shared_ptr<Title>> &index,
        const Actor &actor
);

std::vector<std::shared_ptr<Title>> db_query_9(
        const std::vector<std::shared_ptr<Title>> &db,
        const Actor &actor
);

std::vector<std::shared_ptr<Title>> db_query_10(
        const std::vector<std::shared_ptr<Title>> &db,
        const std::string &genre
);

int db_query_11(
        const std::vector<std::shared_ptr<Title>> &db,
        Type type,
        const std::string &genre
);

int db_query_12(
        const std::vector<std::shared_ptr<Title>> &db,
        const std::string &genre
);


bool operator==(const Actor& actor1, const Actor& actor2);

#endif //DATABASE_QUERIES_H
