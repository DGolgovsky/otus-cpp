#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "container/container.h"

TEST_CASE("Input 0", "[container]") {
    auto custom_list = container<int>{};
    for (uint32_t i = 0; i < 10; ++i) {
        custom_list.emplace(i, i);
    }
    std::stringstream ss;
    for (auto it : custom_list) {
        ss << it;
    }
	std::string str;
	getline(ss, str);
    REQUIRE(str == "0123456789");
}

