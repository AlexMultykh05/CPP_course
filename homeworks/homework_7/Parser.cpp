#include <stack>
#include "Parser.h"
#include "Node.h"
#include "Exception.h"
#include "Expression.h"

using namespace std;

void Parser::clear_cache(stack<Node *> &stackOfOperands) {
    while (!stackOfOperands.empty()) {
        delete stackOfOperands.top();
        stackOfOperands.pop();
    }
}


int Parser::get_precedence(char c) {
    if (c == ADDITION || c == SUBTRACTION)
        return PRIORITY_ADDITION;
    else if (c == MULTIPLICATION || c == DIVISION)
        return PRIORITY_MULTIPLICATION;
    else
        throw ParsingException("Unknown token");
}


Node *Parser::create_number_node(const string &input, size_t &i) {
    int j = i;
    while (isdigit(input[i])) {
        ++i;
    }
    string number = input.substr(j, j - i);
    --i;
    int result = stoi(number);
    return new NumberNode(result);
}


Node *Parser::create_operation_node(char c, stack<Node *> &stackOfOperands) {
    if (stackOfOperands.size() < 2) {
        clear_cache(stackOfOperands);
        throw ParsingException("Missing operands");
    }

    try {
        Node *right = stackOfOperands.top();
        stackOfOperands.pop();
        Node *left = stackOfOperands.top();
        stackOfOperands.pop();
        switch (c) {
            case ADDITION:
                return new AdditionNode(left, right);
            case SUBTRACTION:
                return new SubtractionNode(left, right);
            case MULTIPLICATION:
                return new MultiplicationNode(left, right);
            case DIVISION:
                return new DivisionNode(left, right);
            default:
                return nullptr;
        }
    } catch (bad_alloc &e) {
        clear_cache(stackOfOperands);
        throw MemoryException("Unavailable memory");
    }
}


Node *Parser::parse(const std::string &input) {
   stack<Node *> stackOfOperands;
    stack<char> stackOfOperators;

    try {
        for (size_t i = 0; i < input.length(); i++) {
            char c = input[i];
            if (isdigit(c)) {
                try {
                    Node *node = create_number_node(input, i);
                    try {
                        stackOfOperands.push(node);
                    } catch (bad_alloc &) {
                        clear_cache(stackOfOperands);
                        throw MemoryException("Unavailable memory");
                    }
                } catch (invalid_argument &) {
                    clear_cache(stackOfOperands);
                    throw ParsingException("Malformed number token");

                } catch (out_of_range &) {
                    clear_cache(stackOfOperands);
                    throw ParsingException("Malformed number token");

                }
            } else if (c == OPEN_BRACKET)
                stackOfOperators.push(c);
            else if (c == CLOSE_BRACKET) {
                while (!stackOfOperators.empty() && (stackOfOperators.top() == ADDITION || stackOfOperators.top() == SUBTRACTION || stackOfOperators.top() == MULTIPLICATION || stackOfOperators.top() == DIVISION)) {
                    Node *node = create_operation_node(stackOfOperators.top(), stackOfOperands);
                    stackOfOperators.pop();
                    stackOfOperands.push(node);
                }

                if (stackOfOperators.empty() || stackOfOperators.top() != OPEN_BRACKET) {
                    clear_cache(stackOfOperands);
                    throw ParsingException("Unmatched closing parenthesis");
                }

                stackOfOperators.pop();
            } else if ((c == ADDITION || c == SUBTRACTION || c == MULTIPLICATION || c == DIVISION)) {

                    while (!stackOfOperators.empty() && (stackOfOperators.top() == ADDITION || stackOfOperators.top() == SUBTRACTION || stackOfOperators.top() == MULTIPLICATION || stackOfOperators.top() == DIVISION) && get_precedence(c) <= get_precedence(stackOfOperators.top())) {
                        Node *node = create_operation_node(stackOfOperators.top(), stackOfOperands);
                        stackOfOperators.pop();
                        stackOfOperands.push(node);
                    }

                stackOfOperators.push(c);
            } else {
                clear_cache(stackOfOperands);
                throw ParsingException("Unknown token");
            }
        }
        while (!stackOfOperators.empty()) {
            if (stackOfOperators.top() == OPEN_BRACKET) {
                clear_cache(stackOfOperands);
                throw ParsingException("Unmatched opening parenthesis");
            }

            Node *node = create_operation_node(stackOfOperators.top(), stackOfOperands);
            stackOfOperators.pop();
            stackOfOperands.push(node);
        }
        if (stackOfOperands.size() > 1) {
            clear_cache(stackOfOperands);
            throw ParsingException("Unused operands");
        }

        if (stackOfOperands.empty()) {
            throw ParsingException("Empty expression");
        }
    } catch (ParsingException &e) {
        clear_cache(stackOfOperands);
        throw e;
    } catch (MemoryException &e) {
        clear_cache(stackOfOperands);
        throw e;
    }
    return stackOfOperands.top();
}