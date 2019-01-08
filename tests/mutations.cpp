#include "sanity_mutations.h"
#include "sanity_create.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test mutations array") {
    SECTION("Test build") {
        SanityMutations muts;

        json person = {
            {"_type", "person"},
            {"name", "John Doe"}
        };
        SanityCreate create_mut(person);
        muts.AddMutation(create_mut);

        REQUIRE(
            muts.build() == "{\"mutations\":[{\"createOrReplace\":{\"_type\":\"person\",\"name\":\"John Doe\"}}]}"
        );
    }
}