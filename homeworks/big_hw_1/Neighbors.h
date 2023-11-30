#ifndef BIG_HW_1_NEIGHBORS_H
#define BIG_HW_1_NEIGHBORS_H

#include <iostream>
#include "Symbol.h"

class Neighbors {
public:
    void print(std::ostream &stream = std::cout) const;

    Symbol left_;

    Symbol right_;

    Neighbors(Symbol left, Symbol right);

};

bool operator<(const Neighbors &left, const Neighbors &right);

#endif //BIG_HW_1_NEIGHBORS_H
