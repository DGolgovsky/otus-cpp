#ifndef _FILTER_H_
#define _FILTER_H_

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

namespace ip_filter
{
    using ushort = unsigned short;
    using pool_t = std::vector<std::vector<ushort>>;

    template<typename... Args>
    auto filter(pool_t const &ip_pool, Args... args) noexcept -> pool_t
    {
        pool_t ret;

        std::vector<int> checker{args...};
        auto sz = checker.size();
        std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(ret), [&sz, &checker](auto it){
            return std::equal(it.cbegin(), it.cbegin() + sz, checker.begin());
        });

        return ret;
    }

    auto filter_any(pool_t const &ip_pool, ushort ip) noexcept -> pool_t;

    auto split(std::string const &str) -> std::vector<ushort>;

    auto fill(std::istream &is) -> pool_t;
} // namespace ip_filter

#endif

