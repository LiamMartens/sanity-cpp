#include "sanity_order.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test order build") {
    SECTION("Test single order build") {
        SanityOrder ord("param", false);
        REQUIRE(
            ord.build() == "order(param desc)"
        );
    }

    SECTION("Test multiple order build") {
        SanityOrder ord;
        ord.AddOrderPart("param1");
        ord.AddOrderPart("param2", false);
        REQUIRE(
            ord.build() == "order(param1 asc,param2 desc)"
        );
    }
}