#include <unistd.h>
#include "sanity_client.h"
#include "sanity_query.h"
#include "sanity_filter.h"
#include "sanity_string.h"
#include "sanity_equality_filter.h"
#include "sanity_object.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test client") {
    SECTION("Perform request") {
        SanityClient client("tvkzbtk7", "production", "");
    }
}