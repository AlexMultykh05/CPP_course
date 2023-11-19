#include "Node.h"
#include <iostream>
#include "Exception.h"

Type NumberNode::get_type() const {
    return Type::NUMBER;
}

Type OperationNode::get_type() const {
    return Type::OPERATION;
}

NumberNode::NumberNode(int number) : number_(number) {
}

OperationNode::OperationNode(Node *left, Node *right) : left_(left), right_(right) {
}

int NumberNode::evaluate() const {
    return number_;
}

void NumberNode::print_postfix(std::ostream &stream) const {
    stream << number_;
}

void NumberNode::print_infix(std::ostream &stream) const {
    stream << number_;
}

void OperationNode::print_postfix(std::ostream &stream) const {
    left_->print_postfix(stream);
    stream << " ";
    right_->print_postfix(stream);
    stream << " ";
    stream << get_operator();
}

void OperationNode::print_infix(std::ostream &stream) const {
    if (((OperationNode *) left_)->get_type() == Type::OPERATION) {
        if (((OperationNode *) left_)->get_priority() < get_priority()) {
            stream << "(";
            left_->print_infix(stream);
            stream << ")";
        } else {
            left_->print_infix(stream);
        }
    } else {
        left_->print_infix(stream);
    }

    stream << get_operator();

    if (((OperationNode *) right_)->get_type() == Type::OPERATION) {
        if (((OperationNode *) right_)->get_priority() <= get_priority()) {
            stream << "(";
            right_->print_infix(stream);
            stream << ")";
        } else {
            right_->print_infix(stream);
        }
    } else {
        right_->print_infix(stream);
    }
}

char AdditionNode::get_operator() const {
    return ADDITION;
}

int AdditionNode::evaluate() const {
    return left_->evaluate() + right_->evaluate();
}

int AdditionNode::get_priority() const {
    return PRIORITY_ADDITION;
}

char SubtractionNode::get_operator() const {
    return SUBTRACTION;
}

int SubtractionNode::get_priority() const {
    return PRIORITY_SUBTRACTION;
}

int SubtractionNode::evaluate() const {
    return left_->evaluate() - right_->evaluate();
}

char MultiplicationNode::get_operator() const {
    return MULTIPLICATION;
}

int MultiplicationNode::get_priority() const {
    return PRIORITY_MULTIPLICATION;
}

int MultiplicationNode::evaluate() const {
    return left_->evaluate() * right_->evaluate();
}

char DivisionNode::get_operator() const {
    return DIVISION;
}

int DivisionNode::get_priority() const {
    return PRIORITY_DIVISION;
}

int DivisionNode::evaluate() const {
    int saved = right_->evaluate();

    if (saved == 0)
        throw EvaluationException("Division by zero");

    return left_->evaluate() / saved;
}

Node::~Node() {
}

OperationNode::~OperationNode() {
    if (left_ != nullptr) {
        delete left_;
        left_ = nullptr;
    }
    if (right_ != nullptr) {
        delete right_;
        right_ = nullptr;
    }
}

