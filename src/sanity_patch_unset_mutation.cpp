#include "sanity_patch_unset_mutation.h"

SanityPatchUnsetMutation::SanityPatchUnsetMutation() {
    this->m_type = SanityPartBuilderType::PATCH_UNSET;
}

/**
 * Adds an unset attribute
 * @param string attr
 */
void SanityPatchUnsetMutation::AddAttribute(string attr) {
    this->m_unset_attributes.push_back(attr);
}

/**
 * Creates a copy of the unset patch
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityPatchUnsetMutation::clone() const {
    SanityPatchUnsetMutation* mut = new SanityPatchUnsetMutation();
    for(auto a : this->m_unset_attributes) {
        mut->AddAttribute(a);
    }
    return mut;
}

/**
 * Builds the patch
 * @return string const
 */
string SanityPatchUnsetMutation::build() const  {
    json mut = {
        {"unset", this->m_unset_attributes}
    };
    return mut.dump();
}
