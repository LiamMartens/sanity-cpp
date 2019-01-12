#include "sanity_patch_unset_mutation.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test unset mutation") {
    SECTION("Test build") {
        SanityPatchUnsetMutation mut;
        mut.AddAttribute("firstName");
        mut.AddAttribute("lastName");
        REQUIRE(
            mut.build() == "{\"unset\":[\"firstName\",\"lastName\"]}"
        );
    }
}