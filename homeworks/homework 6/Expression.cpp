#include "Expression.h"

Expression::Expression(Node* root) : root_(root) {
}

Expression::~Expression() {
    delete root_;
    root_ = nullptr;
}

int Expression::evaluate() const {
    return root_->evaluate();
}

void Expression::print_postfix(std::ostream& stream) const {
    root_->print_postfix(stream);
}

void Expression::print_infix(std::ostream& stream) const {
    root_->print_infix(stream);
}