#include <string>
#include "sanity_client.h"
#include "Catch2/single_include/catch2/catch.hpp"

using namespace std;

TEST_CASE("Build API urls", "[client]")
{
    SanityClient client(string("PID"), string("DATASET"), string("TOKEN"));

    SECTION("Should build a regular API url") {
        REQUIRE(client.ApiUrl("documents") == "https://PID.api.sanity.io/v1/documents/DATASET");
    }

    SECTION("Should build a CDN API url") {
        REQUIRE(client.ApiCdnUrl("documents") == "https://PID.apicdn.sanity.io/v1/documents/DATASET");
    }
}