#include <iostream>
#include "Node.h"
#include "Expression.h"
#include "Parser.h"

int main() {

    Node *node = new NumberNode(2);
    delete node;

    Expression e1(
            new MultiplicationNode(
                    new AdditionNode(
                            new NumberNode(2), new NumberNode(3)
                    ),
                    new NumberNode(4)
            )
    );

    e1.print_infix();
    std::cout << std::endl;
    e1.print_postfix();
    std::cout << std::endl;

    Parser::parse("10*2+3*((1+14)-18)-10")->print_postfix(std::cout);
    std::cout << std::endl;
    Parser::parse("(1+22/(11-(0*123)))-3")->print_postfix(std::cout);
    std::cout << std::endl;
    Parser::parse("1*2+3*(4+5)-6")->print_postfix(std::cout);
    std::cout << std::endl;
    Parser::parse("(5-(6*4+5)/2+3*(2/1+4-5))*5-7+2")->print_postfix(std::cout);
    std::cout << std::endl;
    Parser::parse("((((7+4)*2)+((5*(2+(7-(4+2))))/2))+1)")->print_postfix(std::cout);
    std::cout << std::endl;
    Parser::parse("5/(2-2)")->print_postfix(std::cout);
    std::cout << std::endl;

    Parser::parse("10*2+3*((1+14)-18)-10")->print_infix(std::cout);
    std::cout << std::endl;
    Parser::parse("(1+22/(11-(0*123)))-3")->print_infix(std::cout);
    std::cout << std::endl;
    Parser::parse("1*2+3*(4+5)-6")->print_infix(std::cout);
    std::cout << std::endl;
    Parser::parse("(5-(6*4+5)/2+3*(2/1+4-5))*5-7+2")->print_infix(std::cout);
    std::cout << std::endl;
    Parser::parse("((((7+4)*2)+((5*(2+(7-(4+2))))/2))+1)")->print_infix(std::cout);
    std::cout << std::endl;
    Parser::parse("5/(2-2)")->print_infix(std::cout);
    std::cout << std::endl;

    std::cout << Parser::parse("10*2+3*((1+14)-18)-10")->evaluate();
    std::cout << std::endl;
    std::cout << Parser::parse("(1+22/(11-(0*123)))-3")->evaluate();
    std::cout << std::endl;
    std::cout << Parser::parse("1*2+3*(4+5)-6")->evaluate();
    std::cout << std::endl;
    std::cout << Parser::parse("(5-(6*4+5)/2+3*(2/1+4-5))*5-7+2")->evaluate();
    std::cout << std::endl;
    std::cout << Parser::parse("((((7+4)*2)+((5*(2+(7-(4+2))))/2))+1)")->evaluate();
    std::cout << std::endl;


}
