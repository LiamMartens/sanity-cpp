#ifndef SANITY_PATCH_H
#define SANITY_PATCH_H

#include "sanity_part_builder.h"
#include "sanity_mutation.h"
#include "sanity_query.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class SanityPatch : public SanityMutation {
private:
    /** @var The revision id */
    string m_revision_id;
    /** @var The query to use */
    SanityQuery* m_query = nullptr;
    /** @var data */
    json m_data;
public:
    SanityPatch(json data);
    SanityPatch(const SanityPatch& patch);

    void SetRevisionId(string id);
    void SetQuery(const SanityQuery& query);

    json MutationObject() const override;
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_PATCH_H