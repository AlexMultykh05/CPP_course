#include <iostream>

using namespace std;

void print_subset(const char items[], const bool* signature, size_t count){
    bool firstElem = true;
    bool emptySet = true;

    cout << "{ ";

    for(size_t i = 0; i < count; ++i){
        if(signature[i]){
            if(!firstElem)
                cout << ", ";
            cout << items[i];
            firstElem = false;
            emptySet = false;
        }

    }
    if (emptySet)
        cout << "}" << endl;
    else
        cout << " }" << endl;
}

void findAndPrintSubsets(const char items[], bool* signature, size_t count, size_t index){
    if (index == count) {
        print_subset(items, signature, count);
        return;
    }

    signature[index] = true;
    findAndPrintSubsets(items, signature, count, index + 1);

    signature[index] = false;
    findAndPrintSubsets(items, signature, count, index + 1);
}

void generateSubsets(const char items[], size_t count){
    bool* signature = new bool[count];

    findAndPrintSubsets(items, signature, count, 0);

    delete[] signature;
}

int main() {
    const char items[] = { 'A', 'B', 'C', 'D'};
    const size_t count = sizeof(items) / sizeof(items[0]);

    generateSubsets(items, count);

    return 0;
}

