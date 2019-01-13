#ifndef SANITY_PATCH_SET_MUTATION_H
#define SANITY_PATCH_SET_MUTATION_H

#include "sanity_part_builder.h"
#include "sanity_patch_mutation.h"
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class SanityPatchSetMutation : public SanityPatchMutation {
private:
    /** @var Whether to use the if missing flag */
    bool m_set_if_missing = false;
    /** @var set object */
    json m_set_object;
public:
    SanityPatchSetMutation(json data, bool if_missing = false);

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_PATCH_SET_MUTATION_H