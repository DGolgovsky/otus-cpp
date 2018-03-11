#pragma once

template<typename, int>
class Matrix;

#include <map>
#include <tuple>
#include <algorithm>

using place_t = std::pair<int, int>;

#include "MatrixController.h"

template<typename T, int def_value = 0>
class Matrix
{
private:
    std::map<place_t, Value<T, def_value>> m_points;
    using iterator = typename std::map<place_t, Value<T, def_value>>::iterator;

public:
    MatrixController<T, def_value> operator[](int row_) {
        return MatrixController<T, def_value>(*this, row_);
    }

    std::map<place_t, Value<T, def_value>> &get_points() {
        return m_points;
    }

    iterator begin()   { return m_points.begin(); }
    iterator end()     { return m_points.end(); }
    std::size_t size() { return m_points.size(); }

    static auto make_tuple(std::pair<place_t, Value<T, def_value>> it) {
        return std::make_tuple(it.first.first, it.first.second, it.second.get_value());
    }
};
