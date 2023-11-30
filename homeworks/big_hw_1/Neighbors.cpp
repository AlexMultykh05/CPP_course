#include "Neighbors.h"
#include <iostream>

using namespace std;

Neighbors::Neighbors(Symbol left, Symbol right) : left_(left), right_(right) {
}

bool operator<(const Neighbors &left, const Neighbors &right) {
    if (left.left_.get_index() < right.left_.get_index())
        return true;
    else if (left.left_.get_index() > right.left_.get_index())
        return false;
    else if (left.right_.get_index() < right.right_.get_index())
        return true;
    else
        return false;
}

void Neighbors::print(std::ostream &stream) const {
    stream << '(';
    left_.print(stream);
    stream << ", ";
    right_.print(stream);
    stream << ')';
}
