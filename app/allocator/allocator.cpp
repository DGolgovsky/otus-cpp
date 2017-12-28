#include <iostream>
#include <map>
#include "cust_allocator/allocator.h"
#include "container/container.h"

template <typename T>
void fill_container(T &cont, uint32_t sz, bool factorial = true)
{
    if (factorial) {
        auto next = 1;
        cont.emplace(0, next);
        for (uint32_t i = 1; i != sz; ++i) {
            next *= i;
            cont.emplace(i, next);
        }
    } else {
        for (uint32_t i = 0; i < sz; ++i) {
            cont.emplace(i, i);
        }
    }
}

int main(int, char **)
{
    {
        auto std_map = std::map<uint32_t, uint32_t>{};
        fill_container(std_map, 10, true);
    }
    {
        auto custom_map = std::map<uint32_t, uint32_t, std::less<>, alloc::custom_allocator<std::pair<const uint32_t, uint32_t>, 10>>{};
        fill_container(custom_map, 10, true);
        for (auto const &it : custom_map) {
            std::cout << it.first << " " << it.second << std::endl;
        }
    }
    {
        auto custom_list = container<int>{};
        fill_container(custom_list, 10, false);
    }
    {
        auto custom_list = container<int, alloc::custom_allocator<Node<int>, 10>>{};
        fill_container(custom_list, 10, false);
        for(auto it : custom_list) {
            std::cout << it << std::endl;
        }
    }

    return 0;
}

