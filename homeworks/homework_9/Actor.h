#ifndef INC_5TH_HW_ACTOR_H
#define INC_5TH_HW_ACTOR_H

#include <iostream>
#include <string>
constexpr int MIN_ACTOR_YEAR = 1850;
constexpr int MAX_ACTOR_YEAR = 2100;

class Actor {
private:
    std::string name_;
    std::string surname_;
    unsigned short year_;

public:
    Actor(const std::string &name, const std::string &surname, unsigned short year);

    Actor(std::string &&name, std::string &&surname, unsigned short year);

    Actor() = default;

    const std::string &name() const;

    const std::string &surname() const;

    unsigned short year() const;

    void print_json(std::ostream &stream = std::cout) const;

    friend std::istream& operator>>(std::istream& stream, Actor& actor);

};

inline const std::string &Actor::name() const {
    return name_;
}

inline const std::string &Actor::surname() const {
    return surname_;
}

inline unsigned short Actor::year() const {
    return year_;
}

bool operator<(const Actor &actor1, const Actor &actor2);

std::ostream &operator<<(std::ostream &stream, const Actor &actor);

std::istream &operator>>(std::istream &stream, Actor &actor);

#endif //INC_5TH_HW_ACTOR_H
