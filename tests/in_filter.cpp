#include "sanity_in_filter.h"
#include "sanity_string.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Check in filter") {
    SECTION("Check param filter build") {
        SanityInFilter inf("param");
        inf.AddParam(SanityString::QuoteWrap("p1"));
        inf.AddParam(SanityString::QuoteWrap("p2"));

        REQUIRE(
            inf.build() == "param in [\"p1\",\"p2\"]"
        );
    }

    SECTION("Check path filter build") {
        SanityInFilter inf("param");
        inf.SetPathParam("a.b.c.*");

        REQUIRE(
            inf.build() == "param in path(\"a.b.c.*\")"
        );
    }

    SECTION("Check raw filter build") {
        SanityInFilter inf("param");
        inf.SetRawParam("tags");

        REQUIRE(
            inf.build() == "param in tags"
        );
    }
}