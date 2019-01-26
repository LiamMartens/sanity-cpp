#include "sanity_helpers.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test helpers") {
    SECTION("Test oneOf") {
        map<string, bool> oneOf;
        oneOf.insert(pair<string, bool>("a", false));
        oneOf.insert(pair<string, bool>("b", true));
        REQUIRE(
            SanityHelpers::OneOf<string>(oneOf) == "b"
        );
    }

    SECTION("Test oneOf with default") {
        map<string, bool> oneOf;
        oneOf.insert(pair<string, bool>("a", false));
        oneOf.insert(pair<string, bool>("b", false));
        REQUIRE(
            SanityHelpers::OneOf<string>(oneOf, "c") == "c"
        );
    }
}
