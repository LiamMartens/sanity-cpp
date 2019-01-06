#include <nlohmann/json.hpp>
#include "sanity_patch.h"
#include "sanity_query.h"
#include "sanity_filter.h"
#include "sanity_equality_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

using json = nlohmann::json;
using namespace std;

TEST_CASE("Test patch mutation") {
    json data = {
        {"id", 1},
        {"name", {
            {"firstName", "Liam"},
            {"lastName", "Martens"}
        }}
    };

    SanityPatch p(data);

    SECTION("Test regular build") {
        REQUIRE(
            p.build() == "{\"patch\":{\"id\":1,\"name\":{\"firstName\":\"Liam\",\"lastName\":\"Martens\"}}}"
        );
    }

    SECTION("Test query/revision id build") {
        SanityQuery q;
        SanityFilter f;
        f.AddPart(SanityEqualityFilter("param1", SanityEqualityFilterCondition::EQ, "param2"));
        q.SetFilter(f);
        p.SetQuery(q);
        p.SetRevisionId("aaa-bbb");
        REQUIRE(
            p.build() == "{\"patch\":{\"id\":1,\"ifRevisionID\":\"aaa-bbb\",\"name\":{\"firstName\":\"Liam\",\"lastName\":\"Martens\"},\"query\":\"*[param1 == param2]\"}}"
        );
    }
}