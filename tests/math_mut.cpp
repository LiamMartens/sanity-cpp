#include "sanity_patch_math_mutation.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test math mutation") {
    SECTION("Test inc build") {
        SanityPatchMathMutation op("stats.viewCount", (long)2);
        op.AddItem("stats.visitorCount", (long)1);
        REQUIRE(
            op.build() == "{\"inc\":{\"stats.viewCount\":2,\"stats.visitorCount\":1}}"
        );
    }

    SECTION("Test dec build") {
        SanityPatchMathMutation op("stats.viewCount", (long)2);
        op.Dec();
        op.AddItem("stats.visitorCount", (long)1);
        REQUIRE(
            op.build() == "{\"dec\":{\"stats.viewCount\":2,\"stats.visitorCount\":1}}"
        );
    }
}