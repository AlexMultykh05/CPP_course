#ifndef INC_6TH_HW_PARSER_H
#define INC_6TH_HW_PARSER_H

#include <stack>
#include "Node.h"
constexpr char OPEN_BRACKET = '(';
constexpr char CLOSE_BRACKET = ')';

class Parser {
public:
    static Node* parse(const std::string &input);

private:
    static int get_precedence(char c);

    static Node *create_unary_operation_node(char c, std::stack<Node *> &stackOfNodes);

    static Node *create_binary_operation_node(char c, std::stack<Node *> &stackOfNodes);

    static Node *create_leaf_node(const std::string &input, size_t &i, int &index);

    static void clear_cache(std::stack<Node *> &stackOfOperands);

    static void clean_stacks(Node* node, std::stack<Node *> &stackOfOperands, std::stack<char> &stackOfOperators);

    static void process_concatenation(char c, char prevSymbol, std::stack<Node *> &stackOfOperands, std::stack<char> &stackOfOperators);
};

#endif //INC_6TH_HW_PARSER_H
