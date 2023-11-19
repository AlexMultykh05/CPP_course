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

    static Node *create_operation_node(char c, std::stack<Node *> &stackOfNodes);

    static Node *create_number_node(const std::string &input, size_t &i);

    static void clear_cache(std::stack<Node *> &stackOfOperands);
};

#endif //INC_6TH_HW_PARSER_H
