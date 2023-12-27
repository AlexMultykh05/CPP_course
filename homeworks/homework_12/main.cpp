#include "Array.h"

using namespace std;
using namespace lib;

int main() {
    Array<int> array(5);
    Array<int>::iterator it = array.begin();
    array = {1, 2, 3, 4, 5};
    cout << "array: ";
    array.print();
    cout << endl;
    cout << "array.size(): " << array.size() << endl;

    while (array.size() > 0) {
        cout << "array[" << array.size() << "]: " << array[array.size() - 1] << endl;
        array.pop_back();
    }

    cout << "current size: " << array.size() << endl;
    cout << "current capacity: " << array.capacity() << endl;
    cout << "array: ";
    array.print();
    cout << endl;

    array.push_back(1);
    array.push_back(2);
    cout << "current capacity: " << array.capacity() << endl;
    cout << "current size: " << array.size() << endl;

    array.push_back(3);
    array.push_back(4);
    array.push_back(763276);
    array.push_back(6);
    cout << "current capacity: " << array.capacity() << endl;
    cout << "current size: " << array.size() << endl;

    array.pop_back();
    cout << "current capacity: " << array.capacity() << endl;
    cout << "current size: " << array.size() << endl;


    cout << "array: ";
    cout << array << endl;
    cout << "array[0]: " << array[0] << endl;
    cout << "array[1]: " << array[1] << endl;
    cout << "array[2]: " << array[2] << endl;
//    cout << array[7] << endl;
    array.at(2) = 5;
//    array.at(7) = 5;

    cout << "array: ";
    array.print();
    cout << endl;

    array.pop_back();
    array.pop_back();
    array.pop_back();
    array.pop_back();
    array.pop_back();

    cout << "array: ";
    array.print();
    cout << endl;
    cout << "current capacity: " << array.capacity() << endl;
    cout << "current size: " << array.size() << endl;

    array.pop_back();

}
