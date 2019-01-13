#include "sanity_client.h"
#include "sanity_query.h"
#include "sanity_filter.h"
#include "sanity_string.h"
#include "sanity_equality_filter.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test client") {
    SECTION("Perform request") {
        SanityClient client("wfdilxeh", "production", "skJb3kJH3WVlqzJl94OnOXarel3bk2fVcqFdaICIa2VE1SOWbmdBFoJf96pcBHpihBjVS2O48Sqxi7Nr9IMtN436tB4TK2mKF2EP3uq1b2QujmtVDaAsRuuyEzMyQvjMCPFYS17bZ1GkKIOcLA4nVeuPbWk5xRDp5oHeNVaU2Jt2K45ip544");

        SanityEqualityFilter eqf("_type", SanityEqualityFilterCondition::EQ, SanityString::QuoteWrap("person"));
        SanityFilter filter;
        filter.AddPart(eqf);
        SanityQuery query;
        query.SetFilter(filter);

        SanityRequest* req = client.query(query);
        req->DontParseBody();
        thread t = req->perform();
        t.join();
    }
}