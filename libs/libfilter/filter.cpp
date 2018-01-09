#include "filter.h"

namespace ip_filter
{
    using ushort = unsigned short;
    using pool_t = std::vector<std::vector<ushort>>;

    auto filter_any(pool_t const &ip_pool, ushort ip) noexcept -> pool_t
    {
        pool_t ret;
        std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(ret), [&ip](auto it){
            return std::find(it.cbegin(), it.cend(), ip) != it.cend();
        });
        return ret;
    }

    auto split(std::string const &str) -> std::vector<ushort>
    {
        std::vector<ushort> ret;
        std::string::size_type sz;
        ushort count = 0;

        auto sugar = [&str, &sz](auto a, auto b){
            return static_cast<ushort &&>(std::stoi(str.substr(a, b - a), &sz));
        };

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of('.');
        while (stop != std::string::npos) {
            ret.push_back(sugar(start, stop));
            start = stop + 1;
            stop = str.find_first_of('.', start);
            if (++count == 5)
                break;
        }
        ret.push_back(sugar(start, stop));

        return ret;
    }

    auto fill(std::istream &is) -> pool_t
    {
        pool_t ip_pool;

        try {
            std::string line;
            while (std::getline(is, line))
                ip_pool.push_back(split(line));
        } catch(std::exception const &e) {
            std::cerr << e.what() << std::endl;
        }
        return ip_pool;
    }
} // namespace ip_filter

