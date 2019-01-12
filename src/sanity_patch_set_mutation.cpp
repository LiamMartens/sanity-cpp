#include "sanity_patch_set_mutation.h"

SanityPatchSetMutation::SanityPatchSetMutation(json data, bool if_missing) {
    this->m_type = SanityPartBuilderType::PATCH_SET;
    this->m_set_if_missing = if_missing;
    this->m_set_object = data;
}

/**
 * Creates a clone of the patch set
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityPatchSetMutation::clone() const {
    SanityPatchSetMutation* set = new SanityPatchSetMutation(this->m_set_object, this->m_set_if_missing);
    return set;
}

/**
 * Builds the set mutation
 * @return string const
 */
string SanityPatchSetMutation::build() const {
    string cmd = this->m_set_if_missing ? "setIfMissing" : "set";
    json mut = {
        {cmd, this->m_set_object}
    };
    return mut.dump();
}