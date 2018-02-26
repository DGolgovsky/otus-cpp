#include <iostream>
#include <cassert>
#include "Matrix.h"

int main(int, char const **)
{
    int const def_value = 0;
    int const matrix_size = 10;

    Matrix<int, def_value> matrix;

    { /* Task's description checks */
        assert(matrix.size() == 0);

        auto a = matrix[0][0];
        assert(a == def_value);
        assert(matrix.size() == 0);

        matrix[100][100] = 314;
        assert(matrix[100][100] == 314);
        assert(matrix.size() == 1);

        matrix[100][100] = def_value;
        assert(matrix[100][100] == def_value);
        assert(matrix.size() == 0);
    }

    int matrix_index = matrix_size - 1;

    for (int i = 0; i < matrix_size; ++i) {
        matrix[i][i] = i;
        matrix[i][matrix_index - i] = matrix_index - i;
    }

    for (int i = 1; i < matrix_index; ++i) {
        for (int j = 1; j < matrix_index; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << matrix.size() << std::endl;

    int x = 0;
    int y = 0;
    int v = 0;
    for(auto const &cell : matrix) {
        std::tie(x, y, v) = Matrix<int, def_value>::make_tuple(cell);
        std::cout << "[" << x << "," << y << "]" << " = " << v << std::endl;
    }

    return 0;
}
