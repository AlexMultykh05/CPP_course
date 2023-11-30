#ifndef BIG_HW_1_RESULT_H
#define BIG_HW_1_RESULT_H

#include <iostream>
#include <set>
#include "Neighbors.h"
#include "Symbol.h"

class Result {
public:
    std::set<Symbol> starting;
    std::set<Neighbors> neighbors;
    std::set<Symbol> ending;
    bool epsilon;
};

#endif //BIG_HW_1_RESULT_H
