#ifndef BIG_HW_1_SYMBOL_H
#define BIG_HW_1_SYMBOL_H

#include <iostream>

class Symbol {
private:
    char symbol;

    int index;
public:
    int get_index() const;

    void print(std::ostream &stream = std::cout) const;

    Symbol(char symbol, int index);
};

bool operator<(const Symbol &left, const Symbol &right);

#endif //BIG_HW_1_SYMBOL_H
