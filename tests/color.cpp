#include "sanity_color.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test color") {
    SECTION("Hex parse") {
        SanityColor c = "#ff0000";
        REQUIRE(c.R() == 255);
        REQUIRE(c.G() == 0);
        REQUIRE(c.B() == 0);
    }

    SECTION("RGB parse") {
        SanityColor c("rgba(100,200,250 )");
        REQUIRE(c.R() == 100);
        REQUIRE(c.G() == 200);
        REQUIRE(c.B() == 250);
    }

    SECTION("RGBA parse") {
        SanityColor c("rgba(100,200,250,0.5)");
        REQUIRE(c.R() == 100);
        REQUIRE(c.G() == 200);
        REQUIRE(c.B() == 250);
        REQUIRE(c.A() == 0.5f);
    }

    SECTION("To hex test") {
        SanityColor c(10, 20, 30);
        REQUIRE(c.Hex() == "#0a141e");
        REQUIRE(c.Hex(true) == "#0a141eff");
    }

    SECTION("To rgb(a) test") {
        SanityColor c(10, 20, 30);
        REQUIRE(c.Rgb() == "rgb(10,20,30)");
        REQUIRE(c.Rgba() == "rgba(10,20,30,1)");
    }
}