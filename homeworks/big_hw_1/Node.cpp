#include "Node.h"
#include <iostream>
#include "Exception.h"

std::set<Neighbors> union_set_symbol(Result res_left, Result res_right) {
    std::set<Neighbors> result;
    for (auto it: res_left.ending) {
        for (auto it2: res_right.starting) {
            result.insert(Neighbors(it, it2));
        }
    }

    return result;
}

std::set<Neighbors> union_op_neighbors(std::set<Neighbors> set1, std::set<Neighbors> set2) {
    std::set<Neighbors> result;
    for (auto it: set1) {
        result.insert(it);
    }
    for (auto it: set2) {
        result.insert(it);
    }
    return result;
}

std::set<Symbol> OperationNode::union_op_symbols(std::set<Symbol> set1, std::set<Symbol> set2) const {
    std::set<Symbol> result;
    for (auto it: set1) {
        result.insert(it);
    }
    for (auto it: set2) {
        result.insert(it);
    }
    return result;
}

SymbolNode::SymbolNode(Symbol symbol) : symbol_(symbol) {
}

OperationNode::OperationNode(Node *left, Node *right) : left_(left), right_(right) {
}

Result SymbolNode::evaluate() const {
    Result result = Result();
    result.starting.insert(symbol_);
    result.ending.insert(symbol_);
    result.epsilon = false;

    return result;
}

Result EmptyStringNode::evaluate() const {
    Result result = Result();
    result.epsilon = true;
    return result;
}

Result EmptyLanguageNode::evaluate() const {
    Result result = Result();
    result.epsilon = false;
    return result;
}

Result IterationNode::evaluate() const {
    Result res_next = operatorNode_->evaluate();

    Result result = Result();

    result.starting = res_next.starting;
    result.neighbors = union_op_neighbors(res_next.neighbors, union_set_symbol(res_next, res_next));
    result.ending = res_next.ending;
    result.epsilon = true;

    return result;
}

Result AlternationNode::evaluate() const {
    Result res_left = left_->evaluate();
    Result res_right = right_->evaluate();

    Result result = Result();

    result.starting = union_op_symbols(res_left.starting, res_right.starting);
    result.neighbors = union_op_neighbors(res_left.neighbors, res_right.neighbors);
    result.ending = union_op_symbols(res_left.ending, res_right.ending);
    result.epsilon = res_left.epsilon || res_right.epsilon;

    return result;
}

Result ConcatenationNode::evaluate() const {
    Result res_left = left_->evaluate();
    Result res_right = right_->evaluate();

    Result result = Result();

    if (!res_left.epsilon) {
        result.starting = res_left.starting;
    } else {
        result.starting = union_op_symbols(res_left.starting, res_right.starting);
    }

    result.neighbors = union_op_neighbors(res_left.neighbors, res_right.neighbors);
    result.neighbors = union_op_neighbors(result.neighbors, union_set_symbol(res_left, res_right));

    if (!res_right.epsilon) {
        result.ending = res_right.ending;
    } else {
        result.ending = union_op_symbols(res_left.ending, res_right.ending);
    }

    result.epsilon = res_left.epsilon && res_right.epsilon;

    return result;
}

char AlternationNode::get_operator() const {
    return ALTERNATION;
}

char ConcatenationNode::get_operator() const {
    return CONCATENATION;
}

char IterationNode::get_operator() const {
    return ITERATION;
}

int AlternationNode::get_priority() const {
    return PRIORITY_ALTERNATION;
}

int ConcatenationNode::get_priority() const {
    return PRIORITY_CONCATENATION;
}

int IterationNode::get_priority() const {
    return PRIORITY_ITERATION;
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

IterationNode::IterationNode(Node *operatorNode) : operatorNode_(operatorNode) {

}

IterationNode::~IterationNode() {
    if (operatorNode_ != nullptr) {
        delete operatorNode_;
        operatorNode_ = nullptr;
    }
}

