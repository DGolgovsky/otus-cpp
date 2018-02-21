#include <map>
#include <cassert>
#include <iostream>
#include <algorithm>

std::pair<int, int> place(int x, int y)
{
    return std::make_pair<int, int>(reinterpret_cast<int &&>(x), reinterpret_cast<int &&>(y));
}

int damn_main(int, char const **)
{
    const int sz = 10;
    std::map<std::pair<int, int>, int> matrix;


    matrix[place(0, 0)] = 1;

    matrix[place(100, 100)] = 314;

    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            if ((i == j) || ((i + j) == (sz - 1)))
                matrix[place(i, j)] = j;
        }
    }

    for (int i = 1; i < sz-1; ++i) {
        for (int j = 1; j < sz-1; ++j) {
            auto it = std::find_if(matrix.begin(), matrix.end(),
                                   [i, j](const auto& pr) {
                                       if (i == pr.first.first && j == pr.first.second)
                                           std::cout << pr.second << " ";
                                   });
        }
        std::cout << std::endl;
    }

    std::cout << matrix.size() << std::endl;

    return 0;
}