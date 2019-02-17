#include "sanity_string.h"
#include "sanity_defined_filter.h"
#include "sanity_equality_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test string helper") {
    SECTION("Test quote wrap") {
        REQUIRE(
            SanityString::QuoteWrap("word") == "\"word\""
        );
    }

    SECTION("Test vector join") {
        vector<SanityPartBuilder*> v;
        v.push_back(new SanityDefinedFilter("param"));
        v.push_back(new SanityEqualityFilter("left", SanityEqualityFilterCondition::EQ, "right"));
        REQUIRE(
            SanityString::Join(v) == "defined(param),left == right"
        );
    }

    SECTION("Test trim") {
        string inp = "aaabaaaaaa";
        REQUIRE(SanityString::Trim(inp, 'a') == "b");

        string inp2 = "baaa";
        REQUIRE(SanityString::Trim(inp2, 'a') == "b");

        string inp3 = "b...";
        REQUIRE(SanityString::Trim(inp3, '.') == "b");
    }
}