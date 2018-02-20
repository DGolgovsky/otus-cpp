#pragma once

/**
 * @defgroup helpers
 *
 * Helper structs for printing ip addresses as tuples of same types.
 * @{
 */
template <std::size_t I>
struct print_tuple
{
    template <typename Type, typename... Types>
    static constexpr void print(std::tuple<Type, Types...> const &tuple) {
        auto element = std::get<sizeof...(Types) + 1 - I>(tuple);
        static_assert (std::is_same<Type, decltype(element)>::value, "different types in tuple!");

        std::cout << element;
        if (I > 1)
            std::cout << ".";

        print_tuple<I - 1>::print(tuple);
    }
};

template <>
struct print_tuple<0>
{
    template <typename... Types>
    static constexpr void print(std::tuple<Types...> const &) {}
};
/**
 * @}
 */