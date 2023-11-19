#include "Expression.h"
#include "Parser.h"

Expression::Expression(Node *root) : root_(root) {
}

Expression::Expression(const std::string &input) {
    root_ = Parser::parse(input);
}

Expression::~Expression() {
    if (root_ != nullptr){
        delete root_;
        root_ = nullptr;
    }
}

int Expression::evaluate() const {
    return root_->evaluate();
}

void Expression::print_postfix(std::ostream &stream) const {
    root_->print_postfix(stream);
}

void Expression::print_infix(std::ostream &stream) const {
    root_->print_infix(stream);
}
