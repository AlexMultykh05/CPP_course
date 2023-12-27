#include "Actor.h"
#include "Database.h"

Actor::Actor(const std::string &name, const std::string &surname, unsigned short year) : name_(name), surname_(surname),
                                                                                         year_(year)  {
}

Actor::Actor(std::string &&name, std::string &&surname, unsigned short year) : name_(std::move(name)), surname_(std::move(surname)), year_(year) {}

void Actor::print_json(std::ostream &stream) const {
    stream << "{ "
              "name: \"" << name_ << "\", surname: \"" << surname_ << "\", year: " << year_ << " }";
}

bool operator<(const Actor &actor1, const Actor &actor2) {
    if (actor1.surname() < actor2.surname()) {
        return true;
    }
    if (actor1.surname() == actor2.surname()) {
        if (actor1.name() < actor2.name()) {
            return true;
        }
        if (actor1.name() == actor2.name()) {
            if (actor1.year() < actor2.year()) {
                return true;
            }
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &stream, const Actor &actor) {
    actor.print_json(stream);
    return stream;
}


std::istream &operator>>(std::istream &stream, Actor &actor) {
    stream >> actor.name_;
    if (!stream)
        throw Exception{ERROR_NO_FIELD, "Missing attribute <" + NAME + "> in actor "};
    stream >> actor.surname_;
    if (!stream)
        throw Exception{ERROR_NO_FIELD, "Missing attribute <" + SURNAME + "> in actor "};
    stream >> actor.year_;

    if (!stream) {
        throw Exception{ERROR_NO_FIELD, "Missing, invalid or overflow value in attribute <" + YEAR + "> in actor "};
    }

    if (actor.year_ < MIN_ACTOR_YEAR || actor.year_ > MAX_ACTOR_YEAR) {
        throw Exception{ERROR_NO_FIELD, "Integer out of range <1850, 2100> in attribute <" + YEAR + "> in actor "};
    }

    return stream;
}