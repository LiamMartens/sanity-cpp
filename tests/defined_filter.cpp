#include "sanity_defined_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Check defined filter") {
    SECTION("Check filter build") {
        SanityDefinedFilter df("param");
        REQUIRE(
            df.build() == "defined(param)"
        );
    }
}