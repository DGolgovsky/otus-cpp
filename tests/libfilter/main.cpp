#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "libfilter/filter.h"

TEST_CASE("Input 0", "[filter]") {
    auto out0 = cracker::crack(6, "because can do must we what",
                               "wedowhatwemustbecausewecan");
    REQUIRE(out0 == "we do what we must because we can");

    auto out1 = cracker::crack(2, "hello planet", "helloworld");
    REQUIRE(out1 == "WRONG PASSWORD");

    auto out2 = cracker::crack(3, "ab abcd cd", "abcd");
    REQUIRE(out2 == "abcd");
}

TEST_CASE("Input 1", "[filter]") {
    auto out0 = cracker::crack(4, "ozkxyhkcst xvglh hpdnb zfzahm",
                               "zfzahm");
    REQUIRE(out0 == "zfzahm");

    auto out1 = cracker::crack(4, "gurwgrb maqz holpkhqx aowypvopu",
                               "gurwgrb");
    REQUIRE(out1 == "gurwgrb");

    auto out2 = cracker::crack(10,
            "a aa aaa aaaa aaaaa aaaaaa aaaaaaa aaaaaaaa aaaaaaaaa aaaaaaaaaa",
            "aaaaaaaaaab");
    REQUIRE(out2 == "WRONG PASSWORD");
}
