#include <string>
#include "sanity_boolean_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Check boolean filter") {

    SECTION("Check truthy filter build") {
        SanityBooleanFilter bf("param", false);
        REQUIRE(
            bf.build() == "!param"
        );
    }

    SECTION("Check falsey filter build") {
        SanityBooleanFilter bf("param");
        REQUIRE(
            bf.build() == "param"
        );
    }
}