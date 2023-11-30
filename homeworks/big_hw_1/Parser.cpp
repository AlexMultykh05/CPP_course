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
    if (c == ITERATION)
        return PRIORITY_ITERATION;
    else if (c == CONCATENATION)
        return PRIORITY_CONCATENATION;
    else if (c == ALTERNATION)
        return PRIORITY_ALTERNATION;
    else
        throw ParsingException("Unknown token");
}


Node *Parser::create_leaf_node(const string &input, size_t &i, int &index) {
    size_t epsilon = 0;
    size_t empty_set = 0;

    if (input[i] == '\\') {
        int j = i;
            while (i < input.size() && epsilon < EPSILON.length() && input[i] == EPSILON[epsilon]) {
                ++i;
                ++epsilon;
            }
            --i;
            if (epsilon == EPSILON.length()) {
                return new EmptyStringNode();
            }
            i = j;

            while (i < input.size() && empty_set < EMPTY_SET.length() && input[i] == EMPTY_SET[empty_set]) {
                ++i;
                ++empty_set;
            }
            --i;
            if (empty_set == EMPTY_SET.length()) {
                return new EmptyLanguageNode();
            }
        throw ParsingException("Unknown token");
    } else {
        ++index;
        return new SymbolNode(Symbol(input[i], index - 1));
    }
}


Node *Parser::create_binary_operation_node(char c, stack<Node *> &stackOfOperands) {
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
            case ALTERNATION:
                return new AlternationNode(left, right);
            case CONCATENATION:
                return new ConcatenationNode(left, right);
            default:
                return nullptr;
        }
    } catch (bad_alloc &e) {
        clear_cache(stackOfOperands);
        throw MemoryException("Unavailable memory");
    }
}


Node *Parser::create_unary_operation_node(char c, stack<Node *> &stackOfOperands) {
    if (stackOfOperands.empty()) {
        clear_cache(stackOfOperands);
        throw ParsingException("Missing operand");
    }

    try {
        Node *operand = stackOfOperands.top();
        stackOfOperands.pop();

        if (c == ITERATION) {
            return new IterationNode(operand);
        } else {
            return nullptr;
        }

    } catch (bad_alloc &e) {
        clear_cache(stackOfOperands);
        throw MemoryException("Unavailable memory");
    }
}


void Parser::clean_stacks(Node *node, stack<Node *> &stackOfOperands, stack<char> &stackOfOperators) {
    stackOfOperators.pop();
    stackOfOperands.push(node);
}


void
Parser::process_concatenation(char c, char prevSymbol, stack<Node *> &stackOfOperands, stack<char> &stackOfOperators) {
    if (prevSymbol == ')' || isalpha(prevSymbol) || prevSymbol == ITERATION) {
        while (!stackOfOperators.empty() &&
               (stackOfOperators.top() == ALTERNATION || stackOfOperators.top() == CONCATENATION) &&
               get_precedence(c) <= get_precedence(stackOfOperators.top())) {
            Node *node = create_binary_operation_node(stackOfOperators.top(), stackOfOperands);
            clean_stacks(node, stackOfOperands, stackOfOperators);
        }
        stackOfOperators.push(c);
    }
}


Node *Parser::parse(const std::string &input) {
    stack<Node *> stackOfOperands;
    stack<char> stackOfOperators;
    int index = 1;

    try {
        for (size_t i = 0; i < input.length(); i++) {
            char c = input[i];
            char prevSymbol = '_';

            if (i > 0)
                prevSymbol = input[i - 1];

            if (isalpha(c) || c == '\\') {
                process_concatenation(CONCATENATION, prevSymbol, stackOfOperands, stackOfOperators);
                try {
                    Node *node = create_leaf_node(input, i, index);
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
            } else if (c == OPEN_BRACKET) {
                process_concatenation(CONCATENATION, prevSymbol, stackOfOperands, stackOfOperators);
                stackOfOperators.push(c);
            } else if (c == CLOSE_BRACKET) {
                while (!stackOfOperators.empty() &&
                       (stackOfOperators.top() == ALTERNATION || stackOfOperators.top() == CONCATENATION ||
                        stackOfOperators.top() == ITERATION)) {
                    if (stackOfOperators.top() == ITERATION) {
                        Node *node = create_unary_operation_node(stackOfOperators.top(), stackOfOperands);
                        clean_stacks(node, stackOfOperands, stackOfOperators);
                    } else {
                        Node *node = create_binary_operation_node(stackOfOperators.top(), stackOfOperands);
                        clean_stacks(node, stackOfOperands, stackOfOperators);
                    }
                }

                if (stackOfOperators.empty() || stackOfOperators.top() != OPEN_BRACKET) {
                    clear_cache(stackOfOperands);
                    throw ParsingException("Unmatched closing parenthesis");
                }

                stackOfOperators.pop();

            } else if (c == ITERATION) {
                Node *node = create_unary_operation_node(c, stackOfOperands);
                stackOfOperands.push(node);
            } else if ((c == ALTERNATION || c == CONCATENATION)) {
                while (!stackOfOperators.empty() &&
                       (stackOfOperators.top() == ALTERNATION || stackOfOperators.top() == CONCATENATION) &&
                       get_precedence(c) <= get_precedence(stackOfOperators.top())) {
                    Node *node = create_binary_operation_node(stackOfOperators.top(), stackOfOperands);
                    clean_stacks(node, stackOfOperands, stackOfOperators);
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

            if (stackOfOperators.top() == ITERATION) {
                Node *node = create_unary_operation_node(stackOfOperators.top(), stackOfOperands);
                clean_stacks(node, stackOfOperands, stackOfOperators);
            } else {
                Node *node = create_binary_operation_node(stackOfOperators.top(), stackOfOperands);
                clean_stacks(node, stackOfOperands, stackOfOperators);
            }
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