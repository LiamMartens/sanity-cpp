#ifndef SANITY_PATCH_H
#define SANITY_PATCH_H

#include "sanity_part_builder.h"
#include "sanity_mutation.h"
#include "sanity_patch_mutation.h"
#include "sanity_query.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class SanityPatch : public SanityMutation {
private:
    /** @var The id to patch */
    string m_id;
    /** @var The query to use */
    SanityQuery* m_query = nullptr;

    /** @var The patches to apply */
    vector<SanityPatchMutation*> m_patches;
    /** @var The revision id */
    string m_revision_id;

    SanityPatch();
public:
    #pragma region constructors
    SanityPatch(string id);
    SanityPatch(const SanityQuery& query);
    ~SanityPatch();
    #pragma endregion

    void SetRevisionId(string id);
    void AddPatch(const SanityPatchMutation& patch);

    json MutationObject() const override;
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_PATCH_H