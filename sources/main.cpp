#include <iostream>
#include <cassert>
#include "matrix.h"

int main(int, char const **)
{
    int const def_value = 0;
    int const matrix_size = 10;

    matrix<int, def_value> matr;
    assert(matr.size() == 0);

    auto a = matr[0][0];
    assert(a == def_value);
    assert(matr.size() == 0);

    matr[100][100] = 314;
    assert(matr[100][100] == 314);
    assert(matr.size() == 1);

    matr[100][100] = def_value;
    assert(matr[100][100] == def_value);
    assert(matr.size() == 0);

    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            if ((i == j) || ((i + j) == (matrix_size - 1)))
                matr[i][j] = j;
        }
    }

    for (int i = 1; i < matrix_size-1; ++i) {
        for (int j = 1; j < matrix_size-1; ++j) {
            std::cout << matr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << matr.size() << std::endl;

    int x = 0;
    int y = 0;
    int v = 0;
    for(auto c : matr) {
        std::tie(x, y, v) = matrix<int, def_value>::make_tuple(c);
        std::cout << "[" << x << "," << y << "]" << " = " << v << std::endl;
    }

    return 0;
}
