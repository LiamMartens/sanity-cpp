#include <nlohmann/json.hpp>
// #include "sanity_patch.h"
#include "Catch2/single_include/catch2/catch.hpp"

using json = nlohmann::json;
using namespace std;

TEST_CASE("Test patch mutation") {
    // json data = {
    //     {"id", 1},
    //     {"name", {
    //         {"firstName", "Liam"},
    //         {"lastName", "Martens"}
    //     }}
    // };

    // SanityPatch p(data);

//     SECTION("Test regular build") {
//         REQUIRE(
//             p.build() == "{\"patch\":{\"id\":1,\"name\":{\"firstName\":\"Liam\",\"lastName\":\"Martens\"}}}"
//         );
//     }
}