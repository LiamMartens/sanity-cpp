#include <string>
#include "sanity_url.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Build URL") {
    SanityUrl u;

    SECTION("Should build a URL") {
        u.SetScheme("https");
        u.SetHostname("example.com");
        u.SetFragment("page1");
        u.PushPath("foo");
        u.PushPath("bar");
        u.InsertQueryPart("hello", "world");
        u.InsertQueryPart("good", "day");
        REQUIRE(
            u.build() == "https://example.com/foo/bar?good=day&hello=world#page1"
        );
    }
}