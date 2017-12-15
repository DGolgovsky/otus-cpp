//#include "libfilter/filter.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

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

namespace filter {
    using vvs = std::vector<std::vector<std::string>>;

    std::string parser(int a) {
        return std::to_string(a);
    }

    template<typename ...Args>
    std::string parser(Args... args) {
        return parser(args...);
    }

    // TODO debug for many arguments
    template<typename ... Args>
    vvs filter(vvs const &ip_pool, Args... args) {
        vvs ret_vector;
        std::vector<std::string> check_vector;
        check_vector.push_back(parser(args...));

        for (const auto &it : ip_pool) {
            bool checker = true;
            auto ip_part = it.begin();
            for(auto chk : check_vector) {
                if (chk != *ip_part) {
                    checker = false;
                    break;
                }
                ++ip_part;
            }
            if (checker)
                ret_vector.push_back(it);
        }

        return ret_vector;
    }

    vvs filter_any(vvs const &ip_pool, int ip) {
        vvs ret_vector;
        std::string::size_type sz;
        for (const auto &it : ip_pool) {
            for(auto ip_part = it.cbegin(); ip_part != it.cend(); ++ip_part) {
                if (std::stoi(*ip_part, &sz) == ip) {
                    ret_vector.push_back(it);
                    break;
                }
            }
        }
        return ret_vector;
    }

    std::vector<std::string> split(const std::string &str, char d) {
        // ("",  '.') -> [""]
        // ("11", '.') -> ["11"]
        // ("..", '.') -> ["", "", ""]
        // ("11.", '.') -> ["11", ""]
        // (".11", '.') -> ["", "11"]
        // ("11.22", '.') -> ["11", "22"]

        std::vector<std::string> r;

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while (stop != std::string::npos) {
            r.push_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }

        r.push_back(str.substr(start));

        return r;
    }

}

int main(int argc, char const **argv)
{
    std::vector<std::vector<std::string>> ip_pool;

    try {
        std::string line;
        while (std::getline(std::cin, line)) {
            std::vector<std::string> v = filter::split(line, '\t');
            ip_pool.push_back(filter::split(v.at(0), '.'));
        }
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

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

    print_out(ip_pool);
    std::cout << "<<-- ALL -->>" << std::endl;

    // TODO filter by first byte and output
    // ip = filter(1)
    print_out(filter::filter(ip_pool, 1));
    std::cout << "<<-- FILTER(1) -->>" << std::endl;

    // TODO filter by first and second bytes and output
    // ip = filter(46, 70)
    print_out(filter::filter(ip_pool, 46, 70));
    std::cout << "<<-- FILTER(46, 70) -->>" << std::endl;

    // [DONE] Filter by any byte and output
    // ip = filter_any(46)
    print_out(filter::filter_any(ip_pool, 46));
    std::cout << "<<-- FILTER_ANY(46) -->>" << std::endl;

    return 0;
}
