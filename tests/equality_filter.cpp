#include "sanity_equality_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Check equality filter buildup") {
    SanityEqualityFilter eqf("left_param", SanityEqualityFilterCondition::EQ, "right_param");

    SECTION("Check filter build") {
        REQUIRE(
            eqf.build() == "left_param == right_param"
        );
    }

    SECTION("Check copy") {
        SanityEqualityFilter eqf_copy = SanityEqualityFilter(eqf);
        REQUIRE(
            eqf_copy.build() == "left_param == right_param"
        );
    }
}