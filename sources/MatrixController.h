#pragma once

#include "Value.h"

template<typename T, int def_value = 0>
class MatrixController
{
private:
    Matrix<T, def_value> &m_matrix;
    Value<T, def_value> m_new_cell;
    int m_row{};

public:
    explicit MatrixController(Matrix<T, def_value> &matrix_, int row_)
            : m_matrix(matrix_)
            , m_new_cell(Value<T, def_value>(m_matrix, def_value))
            , m_row(row_)
    { }

    Value<T, def_value> &operator[](int col) {
        place_t coord = std::make_pair(m_row, col);
        auto it = m_matrix.get_points().find(coord);
        if (it != m_matrix.get_points().end()) {
            it->second.set_row_col(m_row, col);
            return it->second;
        } else {
            m_new_cell.set_row_col(m_row, col);
            return m_new_cell;
        }
    }
};
