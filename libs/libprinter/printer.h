/**
 * @file   printer.h
 * @author DGolgovsky
 * @date   2018
 * @brief  printer.h for OTUS C++ homework #4
 *
 * @details Contain templates for IP printing
 */

#pragma once

#include <iostream>
#include <bitset>
#include <utility>

#include "print_helper.h"

/**
 * @brief Integral types
 *
 * Prints out contents of an ip address represented as an integral type.
 * Except doubles and strings
 *
 * @tparam T - integral type
 * @param[in] value - argument
 * @return void
 */
template <typename T>
static std::enable_if_t<std::is_integral<T>::value, void> print_ip(T &&value)
{
    std::bitset<8 * sizeof(T)> bit(value);
    auto end = sizeof(T) - 1;

    for (size_t i = 0; i < end; ++i)
        std::cout << std::bitset<8>(bit.to_string(), 8 * i, 8).to_ulong() << ".";

    std::cout << std::bitset<8>(bit.to_string(), 8 * end, 8).to_ulong() << std::endl;
}

/**
 * @brief Containers
 *
 * Prints out contents of an ip address represented as an container (vector or a list).
 * Except std::string
 *
 * @tparam T - container type
 * @param[in] container - container object
 * @return void
 */
template <typename T>
static std::enable_if_t<!std::is_integral<T>::value, void> print_ip(T const &container)
{
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it;
        if (it != std::prev(container.end()))
            std::cout << ".";
    }
    std::cout << std::endl;
}

/**
 * @brief Containers (std::string)
 *
 * Prints out contents of an ip address represented as an container std::string.
 *
 * @tparam T - container type
 * @param[in] container - container object
 * @returns void
 */
template<typename T,
         typename std::enable_if<
                 std::is_same<T, std::string>::value, T*>::type = nullptr>
void print_ip(T &&container)
{
    std::cout << container << std::endl;
}

/**
 * @brief Containers (std::tuple)
 * @warning In this case tuple must be std::tuple with same type of elements (example: std::tuple<int, int, int, int>)
 *
 * Prints out contents of an ip address represented as a tuple.
 * @tparam Types - tuple types
 * @param[in] tuple - function argument
 * @returns void
 */
template <typename... Types>
static void print_ip(std::tuple<Types...> const &tuple)
{
    print_tuple<sizeof...(Types)>::print(tuple);
    std::cout << std::endl;
}