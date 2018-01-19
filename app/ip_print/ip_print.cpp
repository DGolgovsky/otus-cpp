/**
 * \file ip_print.cpp
 *
 * Methods for printing ip addresses represented in different ways.
 */
#include <iostream>
#include <type_traits>
#include <list>
#include <vector>
#include <tuple>
#include <string>


/**
 * @brief Integral types
 *
 * Prints out contents of an ip address represented as an integral type.
 * Except doubles and strings
 */
template <typename T>
static std::enable_if_t<std::is_integral<T>::value, void> ip_print(T value)
{
    while (true)
    {
        std::cout << (value & 0xFF);
        value >>= 8;
        if (value == 0)
        {
            std::cout << std::endl;
            break;
        }
        else
            std::cout << ".";
    }
}

/**
 * @brief Prints out contents of an ip address represented as a vector or a list.
 */
template <typename T>
static std::enable_if_t<!std::is_integral<T>::value, void> ip_print(const T& container)
{
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        std::cout << *it;
        if (it != std::prev(container.end()))
            std::cout << ".";
    }
    std::cout << std::endl;
}

/**
 * \defgroup helpers
 * Helper structs for printing ip addresses as tuples of same types.
 */
/**@{*/
template <size_t I>
struct PrintTuple
{
    template <typename Type0, typename... Types>
    static constexpr void Print(const std::tuple<Type0, Types...>& tuple)
    {
        auto element = std::get<sizeof...(Types) + 1 - I>(tuple);
        static_assert (std::is_same<Type0, decltype(element)>::value, "different types in tuple!");

        std::cout << element;
        if (I > 1)
            std::cout << ".";

        PrintTuple<I - 1>::Print(tuple);
    }
};

template <>
struct PrintTuple<0>
{
    template <typename... Types>
    static constexpr void Print(const std::tuple<Types...>&) {}
};
/**@}*/

/**
 * @brief Prints out contents of an ip address represented as a tuple.
 */
template <typename... Types>
static void ip_print(const std::tuple<Types...>& tuple)
{
    PrintTuple<sizeof...(Types)>::Print(tuple);
    std::cout << std::endl;
}

/**
 * \brief Main program function
 *
 * Used with all c++ programs to init start
 * Main function to demonstrate ip_print
 */
int main(int, char const **)
{
    try
    {
        ip_print(0); ///< 1 byte
        ip_print(1);
        ip_print(255);
        ip_print(256);
        ip_print(1234567890);
        ip_print(1234567890123456);

        ip_print(std::list<int>{0, 1, 2, 3});

        ip_print(std::vector<std::string>{"abc", "def", "gij", "klm", "nop", "rst"});

        ip_print(std::tuple<int, int, int, int>{127, 0, 0, 1});

        /* Another tests */
        int  a = 5;
        char c = 0;
        std::vector<unsigned long> testv = { 1, 2, 3, 4 };

        std::string tests = { "12734" };

        auto tuple_ip = std::make_tuple(192, 168, 3, 17);

        std::tuple<char, unsigned char, long, int> wrong_tuple_ip{ 1, 6, 4444, 66666 };

        ip_print(a);
        ip_print(c);
        ip_print(testv);
        ip_print(tests);
        ip_print(tuple_ip);
        //ip_print(wrong_tuple_ip);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl; ///< console error output
    }

    return 0;
}