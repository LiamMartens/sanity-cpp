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

    SECTION("Test tm to string") {
        tm t;
        t.tm_year = 2019 - 1900;
        t.tm_mon = 1 - 1;
        t.tm_mday = 1;
        t.tm_hour = 10;
        t.tm_min = 0;
        t.tm_sec = 0;

        REQUIRE(
            SanityHelpers::TmToString(t) == "2019-01-01T10:00:00Z"
        );
    }

    SECTION("Test string to tm") {
        tm t = SanityHelpers::TmFromString("2019-01-01T10:00:00Z");
        REQUIRE(t.tm_year == 2019 - 1900);
    }
}
