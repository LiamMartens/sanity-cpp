#include "sanity_select.h"
#include "sanity_conditional.h"
#include "sanity_filter.h"
#include "sanity_equality_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test select statement") {
    SECTION("Test build") {
        SanitySelect sl;

        SanityFilter sf1;
        sf1.AddPart(SanityEqualityFilter("popularity", SanityEqualityFilterCondition::GT, "20"));
        SanityConditional cond1;
        cond1.SetFilter(sf1);
        cond1.SetStringValue("high");
        sl.AddOption(cond1);

        SanityFilter sf2;
        sf2.AddPart(SanityEqualityFilter("popularity", SanityEqualityFilterCondition::GT, "10"));
        SanityConditional cond2;
        cond2.SetFilter(sf2);
        cond2.SetStringValue("medium");
        sl.AddOption(cond2);

        REQUIRE(
            sl.build() == "select(popularity > 20 => \"high\",popularity > 10 => \"medium\")"
        );
    }
}

// popularity > 20 => "high",