#include "sanity_object.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test Sanity Object") {
    SECTION("Test clone") {
        SanityObject o;
        o.SetId("aaa-bbb");
        o.SetKey("key");
        o.SetRevision("ccc-ddd");
        o.SetType("document");
        o.SetCreatedAt("2019-01-01T10:00:00Z");
        o.SetUpdatedAt("2019-01-01T10:00:00Z");

        SanityObject* cloned = o.clone();
        REQUIRE(cloned->Id() == "aaa-bbb");
        REQUIRE(cloned->Revision() == "ccc-ddd");
        REQUIRE(cloned->Type() == "document");
        REQUIRE(cloned->Key() == "key");
        delete cloned;
    }

    SECTION("Test json serializable") {
        SanityObject o;
        o.SetId("aaa-bbb");
        o.SetKey("key");
        o.SetRevision("ccc-ddd");
        o.SetType("document");
        o.SetCreatedAt("2019-01-01T10:00:00Z");
        o.SetUpdatedAt("2019-01-01T10:00:00Z");
        REQUIRE(
            o.toJson().dump() == "{\"_createdAt\":\"2019-01-01T10:00:00Z\",\"_id\":\"aaa-bbb\",\"_key\":\"key\",\"_rev\":\"ccc-ddd\",\"_type\":\"document\",\"_updatedAt\":\"2019-01-01T10:00:00Z\"}"
        );
    }
}