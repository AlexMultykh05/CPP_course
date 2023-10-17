#include <vector>
#include "Options.h"

using namespace std;

int main(int argc, char** argv) {
    args_t arguments(argv + 1, argv + argc);
    bool success = processOptions(arguments);

    // return success ? EXIT_SUCCESS : EXIT_FAILURE;

    return 0;
}
