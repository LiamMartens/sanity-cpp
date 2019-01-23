#include "sanity_reference.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Tests reference") {
    SECTION("Test data") {
        SanityReference ref;
        ref.SetRef("fe5f58d6-f21c-40c0-92fb-58fe8e00238f");
        ref.SetKey("5920ae099e95");
        REQUIRE(
            ref.SaveObject().dump() == "{\"_key\":\"5920ae099e95\",\"_ref\":\"fe5f58d6-f21c-40c0-92fb-58fe8e00238f\",\"_type\":\"reference\"}"
        );
    }
}