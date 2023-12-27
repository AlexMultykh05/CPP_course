#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    Matrix<int, 3, 4> matrix(5);
    Matrix<int, 3, 4> matrix3(1);
    matrix.print();
    cout << endl;
    matrix3.print();
    cout << endl;

    matrix = matrix + matrix3;
    matrix.print();

    for (std::size_t r = 0; r < 3; ++r) {
        for (std::size_t c = 0; c < 4; ++c) {
            matrix.set(r, c, r * 3 + c);
        }
    }
    cout << endl;

    matrix.print();
    cout << endl;
    ++matrix;
    matrix.print();
    cout << endl;

    matrix++;
    matrix.print();
    cout << endl;

    matrix = matrix * 5;
    matrix.print();


    cout << endl;

    const Matrix<int, 4, 5> matrix2(3);
    matrix2.print();
    cout << endl;

    const Matrix<int, 3, 5> res = matrix * matrix2;
    res.print();



    return 0;
}
