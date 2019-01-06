#include "sanity_slice.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test slice build") {
    SECTION("Test single slice") {
        SanitySlice s(1);
        REQUIRE(
            s.build() == "[1]"
        );
    }

    SECTION("Test double slice") {
        SanitySlice s(1, 10);
        REQUIRE(
            s.build() == "[1...10]"
        );
    }
}