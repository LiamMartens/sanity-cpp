#include "sanity_string.h"
#include "sanity_match_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Check sanity match filter") {
    SECTION("Check single filter build") {
        SanityMatchFilter mf("param", SanityString::QuoteWrap("match*"));
        REQUIRE(
            mf.build() == "param match \"match*\""
        );
    }

    SECTION("Check multiple filter build") {
        SanityMatchFilter mf;
        mf.AddParam("param1");
        mf.AddParam("param2");
        mf.AddMatch(SanityString::QuoteWrap("wo*"));
        mf.AddMatch(SanityString::QuoteWrap("zero"));

        REQUIRE(
            mf.build() == "[param1,param2] match [\"wo*\",\"zero\"]"
        );
    }
}