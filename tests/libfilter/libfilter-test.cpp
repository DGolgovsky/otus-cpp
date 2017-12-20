#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "libfilter/filter.h"

TEST_CASE("Input 0", "[fill]") {
    std::stringstream ss;
    ss << "113.162.145.156\t111\t0\n";
    ss << "157.39.22.224\t5\t6\n";
    ss << "79.180.73.190\t2\t1\n";
    auto out = ip_filter::fill(ss);
    
    std::vector<std::vector<unsigned short>> test = {
              {113, 162, 145, 156},
              {157, 39, 22, 224},
              {79, 180, 73, 190}
    };
    
    REQUIRE(out == test);
}

TEST_CASE("Input 1", "[filter]") {
    // cat ip.tsv | ./a.out
    std::stringstream ss;
    ss << "1.231.69.33\n1.87.203.225\n1.70.44.170\n1.29.168.152\n1.1.234.8\n";
    auto test = ip_filter::fill(ss);

    auto out = ip_filter::filter(test, 1);

    REQUIRE(out == test);

}

