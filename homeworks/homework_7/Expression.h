#ifndef INC_6TH_HW_EXPRESSION_H
#define INC_6TH_HW_EXPRESSION_H

#include <iostream>
#include "Node.h"
#include "Exception.h"

class Expression {
private:
    Node* root_;

public:
    Expression(Node* root);
    ~Expression();
    Expression(const std::string& input);
    int evaluate() const;
    void print_postfix(std::ostream& stream = std::cout) const;
    void print_infix(std::ostream& stream = std::cout) const;

};

#endif //INC_6TH_HW_EXPRESSION_H
