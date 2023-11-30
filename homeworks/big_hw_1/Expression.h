#ifndef INC_6TH_HW_EXPRESSION_H
#define INC_6TH_HW_EXPRESSION_H

#include <iostream>
#include "Node.h"
#include "Exception.h"
#include "Result.h"

class Expression {
private:
    Node *root_;

public:
    Expression(Node *root);
    Expression(const std::string& input);
    ~Expression();
    Result evaluate() const;

};

#endif //INC_6TH_HW_EXPRESSION_H
