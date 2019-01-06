#include "sanity_query.h"
#include "sanity_filter.h"
#include "sanity_equality_filter.h"
#include "sanity_defined_filter.h"
#include "sanity_defined_filter.h"
#include "sanity_string.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test query") {
    SanityQuery query;

    SanityFilter filter;
    filter.AddPart(
        SanityEqualityFilter("param1", SanityEqualityFilterCondition::EQ, "param2")
    );
    filter.AddPart(
        SanityDefinedFilter("param3"),
        SanityFilterOperator::AND
    );
    query.SetFilter(filter);

    SanityObjectProjection proj;
    proj.AddProperty(
        SanityObjectProjectionProperty("title")
    );
    proj.AddProperty(
        SanityObjectProjectionProperty("description")
    );
    query.SetProjection(proj);

    SECTION("Test query copy") {
        SanityQuery query_copy = query;

        REQUIRE(
            query.build() == "*[param1 == param2 && defined(param3)]{title,description}"
        );

        REQUIRE(
            query_copy.build() == "*[param1 == param2 && defined(param3)]{title,description}"
        );
    }

    SECTION("Test query clone") {
        SanityQuery* query_clone = (SanityQuery*)query.clone();

        REQUIRE(
            query.build() == "*[param1 == param2 && defined(param3)]{title,description}"
        );

        REQUIRE(
            query_clone->build() == "*[param1 == param2 && defined(param3)]{title,description}"
        );

        delete query_clone;
    }

    SECTION("Test query build") {
        REQUIRE(
            query.build() == "*[param1 == param2 && defined(param3)]{title,description}"
        );
    }

    SECTION("Test subquery build") {
        SanityObjectProjectionProperty subq_prop;
        subq_prop.SetRename("relatedMovies");

        SanityQuery subq;
        SanityFilter subq_filter;
        subq_filter.AddPart(
            SanityEqualityFilter(
                "_type",
                SanityEqualityFilterCondition::EQ,
                SanityString::QuoteWrap("movie")
            )
        );
        subq_filter.AddPart(SanityDefinedFilter("^._id"), SanityFilterOperator::AND);
        subq.SetFilter(subq_filter);
        SanityObjectProjection subq_proj;
        subq.SetProjection(subq_proj);
        subq_prop.SetValue(subq);
        proj.AddProperty(subq_prop);
        query.SetProjection(proj);

        REQUIRE(
            query.build() == "*[param1 == param2 && defined(param3)]{title,description,\"relatedMovies\":*[_type == \"movie\" && defined(^._id)]}}"
        );
    }
}