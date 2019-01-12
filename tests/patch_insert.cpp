#include "sanity_patch_insert_mutation.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test insert mutation") {
    SECTION("Test build") {
        SanityPatchInsertMutation m;
        m.SetAfter("some.array[key == 'abc-123']");
        m.AddItem((string)"a");
        m.AddItem((long)1);
        REQUIRE(
            m.build() == "{\"insert\":{\"after\":\"some.array[key == 'abc-123']\",\"items\":[\"a\",1]}}"
        );
    }
}