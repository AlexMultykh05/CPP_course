#ifndef INC_6TH_HW_NODE_H
#define INC_6TH_HW_NODE_H

#include <iostream>
#include "Result.h"
#include "Symbol.h"

constexpr char CONCATENATION = '.';
constexpr char ALTERNATION = '+';
constexpr char ITERATION = '*';
const std::string EPSILON = "\\epsilon";
const std::string EMPTY_SET = "\\emptyset";
constexpr char OPENING_BRACKET = '(';
constexpr char CLOSING_BRACKET = ')';

constexpr int PRIORITY_ALTERNATION = 1;
constexpr int PRIORITY_CONCATENATION = 2;
constexpr int PRIORITY_ITERATION = 3;


class Node {
public:
    virtual ~Node();

    virtual Result evaluate() const = 0;

};

class SymbolNode final : public Node {
protected:
    Symbol symbol_;

    Result evaluate() const override;

public:
    SymbolNode(Symbol symbol);
};

class EmptyStringNode final : public Node {
protected:
    Result evaluate() const override;
};

class EmptyLanguageNode final : public Node {
protected:
    Result evaluate() const override;

};

class IterationNode final : public Node {
protected:
    Node *operatorNode_;

    char get_operator() const;

public:
    Result evaluate() const override;

    int get_priority() const;

    IterationNode(Node *operatorNode);
    ~IterationNode();

};

class OperationNode : public Node {
protected:
    Node *left_;
    Node *right_;

    virtual char get_operator() const = 0;

public:

    virtual int get_priority() const = 0;

    std::set<Symbol> union_op_symbols(std::set<Symbol> set1, std::set<Symbol> set2) const;

    OperationNode(Node *left, Node *right);

    ~OperationNode() override;
};

class AlternationNode final : public OperationNode {
public:
    char get_operator() const override;

    Result evaluate() const override;

    int get_priority() const override;

    using OperationNode::OperationNode;

};

class ConcatenationNode final : public OperationNode {
public:
    char get_operator() const override;

    Result evaluate() const override;

    int get_priority() const override;

    using OperationNode::OperationNode;

};

std::set<Neighbors> union_set_symbol(Result res_left, Result res_right);
std::set<Neighbors> union_op_neighbors(std::set<Neighbors> set1, std::set<Neighbors> set2);


#endif //INC_6TH_HW_NODE_H
