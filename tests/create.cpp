#include <nlohmann/json.hpp>
#include "sanity_create.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test create mutation") {
    SECTION("Test build") {
        nlohmann::json obj = {
            {"id", 1},
            {"name", {
                {"firstName", "Liam"},
                {"lastName", "Martens"}
            }}
        };
        SanityCreate create(obj, false);
        REQUIRE(
            create.build() == "{\"createOrReplace\":{\"id\":1,\"name\":{\"firstName\":\"Liam\",\"lastName\":\"Martens\"}}}"
        );
    }
}