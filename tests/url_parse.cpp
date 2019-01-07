#include "sanity_url.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test url parsing") {
    SECTION("Test parse complete") {
        SanityUrl url("https://google.com/search/query/param/flag?foo=bar&hello=world#fragment");
        REQUIRE(url.build() == "https://google.com/search/query/param/flag?foo=bar&hello=world#fragment");
    }

    SECTION("Test parse bare") {
        SanityUrl url("https://google.com/");
        REQUIRE(url.build() == "https://google.com");
    }

    SECTION("Test simple parse query") {
        SanityUrl url("https://google.com?hello=world");
        REQUIRE(url.build() == "https://google.com?hello=world");
    }

    SECTION("Test simple fragment") {
        SanityUrl url("https://google.com/#fragment");
        REQUIRE(url.build() == "https://google.com#fragment");
    }
}
