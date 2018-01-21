#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <type_traits>

/*!
	\brief Function object for printing the ip address, represented by a prime number.
	       In this case prime number could be any integer type: short, int, unsigned char, etc.
*/
template <typename Type>
struct print_pod_ip
{
    void operator () (Type ip_addr)
    {
        size_t type_size = sizeof(Type);
        for (int i = 0; i < type_size; ++i)
        {
            if (i != 0) std::cout << ".";
            std::cout << (ip_addr >> (8 * (type_size - i - 1)));
        }
    }
};


/*!
	\brief Function object for printing the ip address, represented by container.
	In this case container could be any sequential container: std::vector<T>, std::list<T>, etc.
*/
template <typename Type>
struct print_complex_ip
{
    void operator () (const Type& ip_addr)
    {
        const auto begin_iter = ip_addr.begin();
        const auto end_iter   = ip_addr.end();

        for (auto i = begin_iter; i != end_iter; ++i)
        {
            if (i != begin_iter) std::cout << ".";
            std::cout << *i;
        }
    }
};


/*!
	\brief Function object for printing the ip address, represented by tuple.
	\warning In this case tuple must be std::tuple with same type of elements (example: std::tuple<int, int, int, int>)
*/
template <typename... Args>
struct print_complex_ip<std::tuple<Args...>>
{
    void operator () (const std::tuple<Args...>& ip_addr)
    {
        static_assert(are_same<Args...>::value, "Elements in tuple aren't same");
        print_impl(ip_addr, std::index_sequence_for<Args...>{});
    }

    template<typename T, typename... TT>
    struct are_same : std::true_type
    {};

    template<typename T1, typename T2, typename... TT>
    struct are_same<T1, T2, TT...>
            : std::integral_constant<bool, (std::is_same<T1, T2>::value) && (are_same<T1, TT...>::value) >
    {};

    template<typename Tuple, size_t... Is>
    void print_impl(const Tuple& tuple, std::index_sequence<Is...>)
    {
        using print_serv_arr = int[];
        print_serv_arr arr = { ((std::cout << (Is == 0 ? "" : ".") << std::get<Is>(tuple)), 0)... };
    }
};

template<typename T>
struct type_is { using type = T; };

template<bool type, typename T, typename U>
struct Conditional : public type_is<T> { ; };

template<typename T, typename U>
struct Conditional <false, T, U> : public type_is<U> { ; };

/*!
	\brief This is a compile time adapter that defines what type of print functional object will be used.
*/
template<typename T>
struct IpPrinter : Conditional<std::is_integral<T>::value, print_pod_ip<T>, print_complex_ip<T>> { ; };


/*!
	This is a public API function for printing ip addresses. You can use it with any data type which represent 		ip address (in, char, string, vector, etc.)
	\param ip_addr - ip address represented by any data type

*/
template<typename T>
void print_ip_address(const T& ip_addr)
{
    typename IpPrinter<T>::type{}(ip_addr);
    std::cout << std::endl;
}
