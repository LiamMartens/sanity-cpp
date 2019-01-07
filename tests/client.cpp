#include "sanity_client.h"
#include "sanity_query.h"
#include "sanity_string.h"
#include "sanity_filter.h"
#include "sanity_equality_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test client") {
    SECTION("Test query") {
        SanityClient client("wfdilxeh", "production", "skJNan8bWg8ry5cl9jdsftiTBaR6YIgIcu9B4frkSwvILdie0qRHdphsOumN6AghWx1Fyqy0z93J2OxaSy1zQOukGt5AdYn96UGDE7CXHebwQrbpNPDT0k5QgG8ZstceeuyNhwpFGcXjn5pb78GIhSFA9VYB00SLimmmXuq7Ypr4JlYDgxWW");

        SanityQuery query;
        SanityFilter filter;
        SanityEqualityFilter eqf("_type", SanityEqualityFilterCondition::EQ, SanityString::QuoteWrap("person"));
        filter.AddPart(eqf);
        query.SetFilter(filter);

        SanityRequest* request = client.query(query);
        thread t = request->perform();
        t.join();
        printf("%s\n", request->Response().Body.c_str());
    }
}