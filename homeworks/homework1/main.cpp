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
        cout << "}\n";
    else
        cout << " }\n";
}

void DFS(const char items[], bool* signature, size_t count, size_t index){
    if (index == count) {
        print_subset(items, signature, count);
        return;
    }

    signature[index] = true;
    DFS(items, signature, count, index + 1);

    signature[index] = false;
    DFS(items, signature, count, index + 1);
}

void findAndPrintSubsets(const char items[], size_t count){
    bool* signature = new bool[count];

    DFS(items, signature, count, 0);

    delete[] signature;
}

int main() {
    const char items[] = { 'A', 'B', 'C', 'D'};
    const size_t count = sizeof(items) / sizeof(items[0]);

    findAndPrintSubsets(items, count);

    return 0;
}

