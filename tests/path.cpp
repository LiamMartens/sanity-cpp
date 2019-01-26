#include "sanity_path.h"
#include "sanity_object_projection.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test path builder") {
    SECTION("Check part copy constructor") {
        SanityPathPart p("hello");
        REQUIRE(p.Part() == "hello");
        SanityPathPart p_copy(p);
        REQUIRE(p_copy.Part() == "hello");
        SanityPathPart p_assigned = p;
        REQUIRE(p_assigned.Part() == "hello");
    }

    SECTION("Check array part build") {
        SanityPathArrayPart p("part");
        REQUIRE(p.build() == "part[]");
        SanityPathPart* p_ref = new SanityPathArrayPart("part");
        REQUIRE(p_ref->build() == "part[]");
        delete p_ref;
    }

    SECTION("Check property part build") {
        SanityPathPropertyPart p("part");
        REQUIRE(p.build() == "part");
        SanityPathPart* p_ref = new SanityPathPropertyPart("part");
        REQUIRE(p_ref->build() == "part");
        delete p_ref;
    }

    SECTION("Check path build") {
        SanityPath p;
        p.AddArrayPart("body");
        p.AddArrayPart("children");
        p.AddPart("text");
        REQUIRE(p.build() == "body[].children[].text");
    }

    SECTION("Check path build") {
        SanityPath p;
        p.AddArrayPart("body");
        p.AddArrayPart("children");
        p.AddPart("text");
        REQUIRE(
            p.build() == "body[].children[].text"
        );
    }

    SECTION("Check path copy constructor") {
        SanityPath p;
        p.AddArrayPart("body");
        p.AddArrayPart("children");
        p.AddPart("text");
        SanityPath* pcopy = new SanityPath(p);
        REQUIRE(
            pcopy->build() == "body[].children[].text"
        );
        delete pcopy;
    }

    SECTION("Check object projection path") {
        SanityPath p;
        p.AddPart("poster");
        p.AddPart("asset");

        SanityObjectProjection proj;
        proj.AddProperty(SanityObjectProjectionProperty("title"));
        proj.AddProperty(SanityObjectProjectionProperty("url"));
        p.AddProjectionPart(proj);
        REQUIRE(
            p.build() == "poster.asset->{title,url}"
        );
    }
}