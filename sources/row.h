#pragma once

#include "value.h"

template<typename T, int def_value>
class row
{
public:
    value<T, def_value> &operator[](int col) {
        coord_t coord = std::make_pair(m_row, col);
        auto it = m_matrix.get_points().find(coord);
        if (it != m_matrix.get_points().end()) {
            it->second.set_row_col(m_row, col);
            return it->second;
        } else {
            m_new_cell.set_row_col(m_row, col);
            return m_new_cell;
        }
    }

    row(matrix<T, def_value> &matrix_, int row_)
            : m_matrix(matrix_)
            , m_new_cell(value<T, def_value>(m_matrix, def_value))
            , m_row(row_)
    { }

private:
    matrix<T, def_value> &m_matrix;
    value<T, def_value> m_new_cell;
    int m_row;
};
