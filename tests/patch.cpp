#include "sanity_patch.h"
#include "sanity_patch_unset_mutation.h"
#include "sanity_patch_set_mutation.h"
#include "sanity_patch_math_mutation.h"
#include "sanity_patch_insert_mutation.h"
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("Test patch mutation") {
    SECTION("Test build") {
        SanityPatch patch("my-id");

        json set_data = {{"name.first", "John"}};
        SanityPatchSetMutation set_patch(set_data);
        patch.AddPatch(set_patch);

        SanityPatchUnsetMutation unset_patch;
        unset_patch.AddAttribute("name.last");
        patch.AddPatch(unset_patch);

        SanityPatchMathMutation math_patch("stats.visitorCount", (long)1);
        patch.AddPatch(math_patch);

        SanityPatchInsertMutation ins_patch;
        json ins_data = {
            {"_type", "reference"},
            {"_ref", "person-1234"}
        };
        ins_patch.SetAfter("people[-1]");
        ins_patch.AddItem(ins_data);
        patch.AddPatch(ins_patch);

        REQUIRE(
            patch.build() == "{\"patch\":{\"id\":\"my-id\",\"inc\":{\"stats.visitorCount\":1},\"insert\":{\"after\":\"people[-1]\",\"items\":[{\"_ref\":\"person-1234\",\"_type\":\"reference\"}]},\"set\":{\"name.first\":\"John\"},\"unset\":[\"name.last\"]}}"
        );
    }
}
