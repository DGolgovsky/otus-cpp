#pragma once

template<typename T, int default_value>
class matrix;

template<typename T, int def_value = 0>
class value
{
public:
    value(matrix<T, def_value> &matrix_, int val_)
            : m_matrix(matrix_)
            , m_value(val_)
    { }

    void set_row_col(int row_, int col_) {
        m_row = row_;
        m_col = col_;
    }

    void operator=(const int& val) {
        coord_t coord = std::make_pair(m_row, m_col);
        if (val == def_value) {
            auto it = m_matrix.get_points().find(coord);
            if (it != m_matrix.get_points().end())
                m_matrix.get_points().erase(it);
        } else {
            m_matrix.get_points().insert(std::make_pair(coord, value(m_matrix, val)));
        }
    }

    friend bool operator==(value<T, def_value> &lhs, T const &rhs) {
        return lhs.get_value() == rhs;
    }

    friend std::ostream &operator<<(std::ostream &os, value<T, def_value> const &obj) {
        if (obj.m_value == def_value)
            os << def_value;
        else
            os << obj.m_value;
        return os;
    }

    T get_value() const {
        return m_value;
    }

private:
    matrix<T, def_value> &m_matrix;
    T m_value = def_value;
    int m_row{};
    int m_col{};
};
