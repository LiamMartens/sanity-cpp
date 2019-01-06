#include "sanity_filter.h"
#include "sanity_equality_filter.h"
#include "sanity_defined_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test filter building") {
    SECTION("Test filter part build") {
        SanityEqualityFilter eqf("param", SanityEqualityFilterCondition::EQ, "param2");
        SanityFilterPart part(eqf, SanityFilterOperator::AND);
        REQUIRE(
            part.build() == "&& param == param2"
        );
    }

    SECTION("Test filter build") {
        SanityFilter f;
        f.AddPart(
            SanityFilterPart(
                SanityDefinedFilter("param")
            )
        );
        f.AddPart(
            SanityFilterPart(
                SanityEqualityFilter(
                    "param",
                    SanityEqualityFilterCondition::EQ,
                    "param2"
                )
            ),
            SanityFilterOperator::AND
        );
        REQUIRE(
            f.build() == "defined(param) && param == param2"
        );
    }
}