#include <iostream>

#include "sanity_part_builder.h"
#include "sanity_path.h"
#include "sanity_object_projection.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test object projection") {
    SECTION("Test property builder") {
        SanityObjectProjectionProperty prop;
        SanityPath prop_path;
        prop_path.AddPart("prop");
        prop.SetValue(prop_path);
        prop.SetRename("renamed_prop");
        // REQUIRE(prop.build() == "\"renamed_prop\":prop");

        SanityObjectProjectionProperty prop_copy = prop;
        REQUIRE(prop_copy.build() == "\"renamed_prop\":prop");

        SanityObjectProjectionProperty* prop_ref = new SanityObjectProjectionProperty(prop);
        REQUIRE(prop_ref->build() == "\"renamed_prop\":prop");
        delete prop_ref;
    }

    SECTION("Test path based property") {
        SanityObjectProjection proj;
        SanityPath p;
        p.AddPart("poster");
        p.AddPart("asset");
        SanityObjectProjectionProperty prop;
        prop.SetValue(p);
        prop.SetRename("poster");
        REQUIRE(prop.build() == "\"poster\":poster.asset");
    }

    SECTION("Test projection build") {
        SanityObjectProjection proj;
        SanityObjectProjectionProperty title_prop;
        SanityPath title_prop_path;
        title_prop_path.AddPart("title");
        title_prop.SetValue(title_prop_path);
        proj.AddProperty(title_prop);

        SanityPath p;
        p.AddPart("poster");
        p.AddPart("asset");
        SanityObjectProjectionProperty prop;
        prop.SetValue(p);
        prop.SetRename("poster");
        proj.AddProperty(prop);

        REQUIRE(
            proj.build() == "{title,\"poster\":poster.asset}"
        );
    }

    SECTION("Test subprojection build") {
        SanityObjectProjection proj;
        SanityPath title_path;
        title_path.AddPart("title");
        SanityObjectProjectionProperty title_prop;
        title_prop.SetValue(title_path);
        proj.AddProperty(title_prop);

        SanityPath path;
        path.AddPart("asset");
        SanityObjectProjection path_proj;
        path_proj.AddProperty(SanityObjectProjectionProperty("path"));
        path_proj.AddProperty(SanityObjectProjectionProperty("url"));
        path.AddProjectionPart(path_proj);
        SanityObjectProjection subproj;
        SanityObjectProjectionProperty path_prop;
        path_prop.SetValue(path);
        subproj.AddProperty(path_prop);
        SanityObjectProjectionProperty poster_prop("poster");
        poster_prop.SetSubprojection(subproj);
        proj.AddProperty(poster_prop);
        REQUIRE(
            proj.build() == "{title,poster{asset->{path,url}}}"
        );
    }
}