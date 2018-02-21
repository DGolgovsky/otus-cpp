#pragma once
#include <map>
#include <tuple>
#include <algorithm>

using coord_t = std::pair<int, int>;

#include "row.h"

template<typename T, int def_value = 0>
class matrix
{
    using iterator = typename std::map<coord_t, value<T, def_value>>::iterator;

public:
    row<T, def_value> operator[](int row_) {
        return row<T, def_value>(*this, row_);
    }

    std::map<coord_t, value<T, def_value>> &get_points() {
        return m_points;
    }

    iterator begin()   { return m_points.begin(); }
    iterator end()     { return m_points.end(); }
    std::size_t size() { return m_points.size(); }

    static std::tuple<int, int, int> make_tuple(std::pair<coord_t, value<T, def_value>> it) {
        int x = it.first.first;
        int y = it.first.second;
        T v = it.second.get_value();

        return std::make_tuple(x, y, v);
    }

private:
    std::map<coord_t, value<T, def_value>> m_points;
};
