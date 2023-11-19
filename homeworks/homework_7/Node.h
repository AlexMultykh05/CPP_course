#ifndef INC_6TH_HW_NODE_H
#define INC_6TH_HW_NODE_H

#include <iostream>

constexpr char ADDITION = '+';
constexpr char SUBTRACTION = '-';
constexpr char MULTIPLICATION = '*';
constexpr char DIVISION = '/';

constexpr int PRIORITY_ADDITION = 1;
constexpr int PRIORITY_SUBTRACTION = 1;
constexpr int PRIORITY_MULTIPLICATION = 2;
constexpr int PRIORITY_DIVISION = 2;


enum class Type {
    NUMBER,
    OPERATION
};

class Node {
protected:
    virtual Type get_type() const = 0;

public:
    virtual ~Node();

    virtual int evaluate() const = 0;

    virtual void print_postfix(std::ostream &stream) const = 0;

    virtual void print_infix(std::ostream &stream) const = 0;
};

class NumberNode final : public Node {
protected:
    int number_;

    Type get_type() const override;

    int evaluate() const override;

public:

    void print_postfix(std::ostream &stream) const override;

    void print_infix(std::ostream &stream) const override;

    NumberNode(int number);
};

class OperationNode : public Node {
protected:
    Node *left_;
    Node *right_;

    virtual char get_operator() const = 0;

public:

    virtual int get_priority() const = 0;

    Type get_type() const override;

    void print_postfix(std::ostream &stream) const override;

    void print_infix(std::ostream &stream) const override;

    OperationNode(Node *left, Node *right);

    ~OperationNode() override;
};

class AdditionNode final : public OperationNode {
public:
    char get_operator() const override;

    int evaluate() const override;

    int get_priority() const override;

    using OperationNode::OperationNode;

};

class SubtractionNode final : public OperationNode {
public:
    char get_operator() const override;

    int evaluate() const override;

    int get_priority() const override;

    using OperationNode::OperationNode;

};

class MultiplicationNode final : public OperationNode {
public:
    char get_operator() const override;

    int evaluate() const override;

    int get_priority() const override;

    using OperationNode::OperationNode;

};

class DivisionNode final : public OperationNode {
public:
    char get_operator() const override;

    int evaluate() const override;

    int get_priority() const override;

    using OperationNode::OperationNode;

};


#endif //INC_6TH_HW_NODE_H
