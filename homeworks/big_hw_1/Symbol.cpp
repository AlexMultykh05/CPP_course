#include "Symbol.h"

void Symbol::print(std::ostream &stream) const {
    stream << symbol << index;
}

int Symbol::get_index() const {
    return index;
}

Symbol::Symbol(char symbol, int index) : symbol(symbol), index(index) {
}

bool operator<(const Symbol &left, const Symbol &right) {
    return left.get_index() < right.get_index();
}