#include <iostream>
#include "Node.h"
#include "Expression.h"
#include "Parser.h"
#include "Result.h"

using namespace std;

void print(const Result& r)
{
    for (Symbol i : r.starting)
    {
        i.print();
        cout << ' ';
    }
    cout << '\n';
    for (Neighbors i : r.neighbors)
    {
        i.print();
        cout << ' ';
    }
    cout << '\n';
    for (Symbol i : r.ending)
    {
        i.print();
        cout << ' ';
    }
    cout << '\n';
    cout << r.epsilon << '\n';
}

int main() {
    Expression e = Expression("(ab+\\epsilon)(bb)*");
    print(e.evaluate());
}