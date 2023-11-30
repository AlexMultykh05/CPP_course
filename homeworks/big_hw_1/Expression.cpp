#include "Expression.h"
#include "Parser.h"

Expression::Expression(Node *root) : root_(root) {
}

Expression::Expression(const std::string &input) {
    root_ = Parser::parse(input);
}

Expression::~Expression() {
    if (root_ != nullptr) {
        delete root_;
        root_ = nullptr;
    }
}

Result Expression::evaluate() const {
    return root_->evaluate();
}


