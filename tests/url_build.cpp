#include <string>
#include "sanity_url.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Build URL") {
    SanityUrl u;
    u.SetScheme(SanityUrl::SCHEME_HTTPS);
    u.SetHostname("example.com");
    u.PushPath("foo");
    u.PushPath("bar");
    u.SetFragment("page1");
    u.InsertQueryPart("hello", "world");
    u.InsertQueryPart("good", "day");

    SECTION("Should build a URL") {
        REQUIRE(
            u.build() == "https://example.com/foo/bar?good=day&hello=world#page1"
        );
    }

    SECTION("Should copy a url object") {
        SanityUrl u_copy = u;
        REQUIRE(
            u_copy.build() == "https://example.com/foo/bar?good=day&hello=world#page1"
        );
        
        SanityUrl* u_clone = (SanityUrl*)u.clone();
        REQUIRE(
            u_clone->build() == "https://example.com/foo/bar?good=day&hello=world#page1"
        );
    }
}