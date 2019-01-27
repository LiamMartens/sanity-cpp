#include "sanity_object.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test Sanity Object") {
    SECTION("Test clone") {
        SanityObject o;
        o.SetId("aaa-bbb");
        o.SetRevision("ccc-ddd");
        o.SetType("document");
        o.SetCreatedAt("2019-01-01T10:00:00Z");
        o.SetUpdatedAt("2019-01-01T10:00:00Z");

        SanityObject* cloned = o.clone();
        REQUIRE(cloned->Id() == "aaa-bbb");
        REQUIRE(cloned->Revision() == "ccc-ddd");
        REQUIRE(cloned->Type() == "document");
        delete cloned;
    }
}