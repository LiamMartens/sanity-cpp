#ifndef SANITY_PATCH_UNSET_MUTATION_H
#define SANITY_PATCH_UNSET_MUTATION_H

#include <string>
#include <nlohmann/json.hpp>
#include "sanity_patch_mutation.h"

using json = nlohmann::json;
using namespace std;

class SanityPatchUnsetMutation : public SanityPatchMutation {
private:
    json m_unset_attributes;
public:
    SanityPatchUnsetMutation();
    void AddAttribute(string attr);

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_PATCH_UNSET_MUTATION_H