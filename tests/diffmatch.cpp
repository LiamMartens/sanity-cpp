#include "sanity_patch_diffmatch_mutation.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test diffmatch patch") {
    SECTION("Test build") {
        SanityPatchDiffMatchMutation mut;
        mut.AddDiffMatch("aboutADog", "@@ -1,13 +1,12 @@\n The \n-rabid\n+nice\n  dog\n");
        string b = mut.build();
        REQUIRE(
            mut.build() == "{\"diffMatchPatch\":{\"aboutADog\":\"@@ -1,13 +1,12 @@\\n The \\n-rabid\\n+nice\\n  dog\\n\"}}"
        );
    }
}
