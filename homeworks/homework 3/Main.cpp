#include <iostream>
#include <vector>
#include "Options.h"

using namespace std;

int main(int argc, char **argv) {
    Options options;
    args_t arguments(argv + 1, argv + argc);
    bool success = processOptions(arguments, options);
    cout << endl;
    printStatus(options);
    cout << endl;

    cout << "Intended exit code <" << (success ? '1' : '0') << '>' << endl;


    // return success ? EXIT_SUCCESS : EXIT_FAILURE;

    return 0;
}
