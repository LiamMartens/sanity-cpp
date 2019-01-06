#include "sanity_delete.h"
#include "sanity_query.h"
#include "sanity_filter.h"
#include "sanity_equality_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test delete mutation") {
    SECTION("Test id build") {
        SanityDelete del("10");
        REQUIRE(
            del.build() == "{\"delete\":{\"id\":\"10\"}}"
        );
    }

    SECTION("Test query build") {
        SanityFilter f;
        f.AddPart(SanityEqualityFilter("param1", SanityEqualityFilterCondition::EQ, "param2"));
        SanityQuery q;
        q.SetFilter(f);
        SanityDelete del(q);
        REQUIRE(
            del.build() == "{\"delete\":{\"query\":\"*[param1 == param2]\"}}"
        );
    }
}