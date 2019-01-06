#include "sanity_references_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test references filter build") {
    SECTION("Check build") {
        SanityReferencesFilter rf("^.param");
        REQUIRE(
            rf.build() == "references(^.param)"
        );
    }
}