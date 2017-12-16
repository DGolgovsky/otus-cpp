#include <algorithm>
#include "libfilter/filter.h"

template<typename T>
void print_out(std::vector<std::vector<T>> const &v) noexcept {
    for (const auto &ip : v) {
        for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
            if (ip_part != ip.cbegin()) {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<std::vector<std::string>> ip_pool = ip_filter::fill(std::cin);

    // [DONE] Reverse lexicographically sort
    std::sort(ip_pool.begin()
             ,ip_pool.end()
             ,[](auto const &lhs, auto const &rhs) { // Comparator
                std::string::size_type sz;
                for (std::size_t i = 0; i != 4; ++i) {
                    // Comparison with current column
                    if (std::stoi(lhs[i], &sz) < std::stoi(rhs[i], &sz))
                        return false;
                    if (std::stoi(lhs[i], &sz) > std::stoi(rhs[i], &sz))
                        return true;
                    // lhs[i] == rhs[i],
                    // so check with next sorting column
                }
                return false;
            }
    );

    print_out(ip_pool); // ALL

    // [DONE] Filter by first byte and output
    // ip = ip_filter(1)
    print_out(ip_filter::filter(ip_pool, 1)); // FILTER(1)

    // [DONE] Filter by first and second bytes and output
    // ip = ip_filter(46, 70)
    print_out(ip_filter::filter(ip_pool, 46, 70)); // FILTER(46, 70)

    // [DONE] Filter by any byte and output
    // ip = filter_any(46)
    print_out(ip_filter::filter_any(ip_pool, 46)); // FILTER_ANY(46)

    return 0;
}
