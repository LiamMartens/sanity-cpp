#include "sanity_patch_set_mutation.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test set patch") {
    SECTION("Test build") {
        json data = {
            {"firstName", "Liam"},
            {"lastName", "Martens"}
        };
        SanityPatchSetMutation mut(data, true);
        REQUIRE(
            mut.build() == "{\"setIfMissing\":{\"firstName\":\"Liam\",\"lastName\":\"Martens\"}}"
        );
    }
}