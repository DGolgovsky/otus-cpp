#ifndef _FILTER_H_
#define _FILTER_H_

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

/**
 * IP Filter main header namespace
 */
namespace ip_filter
{
    using ushort = unsigned short;
    using pool_t = std::vector<std::vector<ushort>>;

    /**
     * \brief Filter with template
     *
     * Analogue of filter_any function.
     * Matching with template
     */
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

    /**
     * Filter of entire pool for any match
     */
    auto filter_any(pool_t const &ip_pool, ushort ip) noexcept -> pool_t;

    /**
     * Splitting input stream in values
     */
    auto split(std::string const &str) -> std::vector<ushort>;

    /**
     * Used to filling main pool of addr
     */
    auto fill(std::istream &is) -> pool_t;
} // namespace ip_filter

#endif

