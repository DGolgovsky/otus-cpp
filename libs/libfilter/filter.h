#ifndef _FILTER_H_
#define _FILTER_H_

#include <vector>
#include <string>
#include <iostream>

namespace ip_filter
{
    using vvs = std::vector<std::vector<std::string>>;

    template <typename T>
    void variadic_vector_emplace(std::vector<T>&) {}

    template<typename T, typename First, typename... Args>
    void variadic_vector_emplace(std::vector<T> &v, First &&first, Args &&... args) {
        v.emplace_back(std::forward<First>(first));
        variadic_vector_emplace(v, std::forward<Args>(args)...);
    }

    template<typename... Args>
    std::vector<std::vector<std::string>> filter(vvs const &ip_pool, Args... args) noexcept {
        vvs ret_vector;
        std::vector<int> check_vector;
        variadic_vector_emplace(check_vector, std::forward<Args>(args)...);

        for (auto const &it : ip_pool) {
            bool checker = true;
            auto ip_part = it.cbegin();
            for(auto const &chk : check_vector) {
                if (std::to_string(chk) != *ip_part) {
                    checker = false;
                    break;
                } else {}
                ++ip_part;
            }
            if (checker)
                ret_vector.push_back(it);
        }

        return ret_vector;
    }

    vvs filter_any(vvs const &ip_pool, int ip) noexcept {
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

    std::vector<std::string> split(std::string const &str, char d) {
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

    std::vector<std::vector<std::string>> fill(std::istream &is) {
        std::vector<std::vector<std::string>> ip_pool;
        try {
            std::string line;
            while (std::getline(is, line)) {
                std::vector<std::string> v = split(line, '\t');
                ip_pool.push_back(split(v.at(0), '.'));
            }
        } catch(std::exception const &e) {
            std::cerr << e.what() << std::endl;
        }
        return ip_pool;
    }

}

#endif
