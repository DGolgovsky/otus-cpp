#include "cracker.h"

namespace cracker {
static std::set<std::string> cache;

template <class S, class L>
inline bool is_valid(std::string &login_attempts, S &pass, L &out)
{
    bool ans = false;
    auto search = cache.find(login_attempts);
    if (search != cache.end())
        return false;

    search = pass.find(login_attempts);
    if (search != pass.end()) {
        out.push_back(login_attempts);
        return true;
    } else {
        cache.insert(login_attempts);
    }

    for (size_t i = 0; i < login_attempts.length(); ++i) {
        std::string left = login_attempts.substr(0, i);
        std::string right = login_attempts.substr(i);
        ans = is_valid(left, pass, out) && is_valid(right, pass, out);
        if (ans)
            return true;
    }
    return ans;
}

std::string crack(unsigned int N, std::string &&passwds, std::string &&login_attempts)
{
    std::set<std::string> pass;
    std::list<std::string> out;
    std::string result = "";

    std::istringstream ss(passwds);
    std::string tmp;
    while ((ss >> tmp) || N > 0) {
        pass.insert(tmp);
        --N;
    }

    bool res = is_valid(login_attempts, pass, out);
    if (res) {
        auto first = std::begin(out);
        for (auto it = first; it != std::end(out); ++it) {
            if (it != first)
                result += " ";
            result += *it;
        }
    } else {
        result = "WRONG PASSWORD";
    }

    return result;
}
}
