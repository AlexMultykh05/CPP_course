#ifndef INC_6TH_HW_EXPRESSION_H
#define INC_6TH_HW_EXPRESSION_H

#include <iostream>
#include "Node.h"

class Expression {
private:
    Node* root_;

public:
    Expression(Node* root);
    ~Expression();
    int evaluate() const;
    void print_postfix(std::ostream& stream = std::cout) const;
    void print_infix(std::ostream& stream = std::cout) const;

};

#endif //INC_6TH_HW_EXPRESSION_H
