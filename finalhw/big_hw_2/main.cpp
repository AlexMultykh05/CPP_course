#include "Array.h"
#include "Graph.h"

using namespace std;
using namespace lib;

int main() {

    UndirectedGraph<string, string> g;
    g.import("/Users/alexmultykh/Desktop/uni/second_year/1st_semester/HW/C++_hw/11_12th_hw/graph.txt");
    cout << g;
    cout << endl;
    g.edges().printMatrix();
    cout << endl;
}
