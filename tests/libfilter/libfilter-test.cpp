#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "libfilter/filter.h"

TEST_CASE("Input 0", "[split]") {
	// cat ip.tsv | ./a.out
    //auto out0 = filter::split("192.168.0.1\t10\t20", '\t');
    //REQUIRE(out0 == "192.168.0.1");

}

TEST_CASE("Input 1", "[filter]") {
    auto out0 = filter::filter();
    REQUIRE(out0 == "");

    auto out1 = filter::filter();
    REQUIRE(out1 == "");

    auto out2 = filter::filter();
    REQUIRE(out2 == "");
}
