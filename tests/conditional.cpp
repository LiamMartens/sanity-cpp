#include "sanity_conditional.h"
#include "sanity_equality_filter.h"
#include "sanity_object_projection.h"
#include "sanity_query.h"
#include "sanity_string.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test conditional") {
    SanityFilter sf;
    sf.AddPart(SanityEqualityFilter("popularity", SanityEqualityFilterCondition::LT, "20"));

    SanityConditional cond;
    cond.SetFilter(sf);

    SECTION("Test simple conditional build") {
        cond.SetStringValue("medium");

        REQUIRE(
            cond.build() == "popularity < 20 => \"medium\""
        );
    }

    SECTION("Test projection build") {
        SanityObjectProjection cond_proj;

        SanityQuery query;
        SanityFilter filter;
        filter.AddPart(SanityEqualityFilter("_type", SanityEqualityFilterCondition::EQ, SanityString::QuoteWrap("award")));
        query.SetFilter(filter);
        SanityObjectProjection query_proj;
        query_proj.AddProperty(SanityObjectProjectionProperty("title"));
        query.SetProjection(query_proj);

        SanityObjectProjectionProperty query_prop;
        query_prop.SetRename("awards");
        query_prop.SetSubquery(query);

        cond_proj.AddProperty(query_prop);

        cond.SetBuilder(cond_proj);

        REQUIRE(
            cond.build() == "popularity < 20 => {\"awards\":*[_type == \"award\"]{title}}"
        );
    }
}