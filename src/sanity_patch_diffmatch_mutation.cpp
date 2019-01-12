#include "sanity_patch_diffmatch_mutation.h"

SanityPatchDiffMatchMutation::SanityPatchDiffMatchMutation() {
    this->m_type = SanityPartBuilderType::PATCH_DIFFMATCH;
}

/**
 * Adds a diff match patch for a certain key
 * @param string key
 * @param string dffm
 */
void SanityPatchDiffMatchMutation::AddDiffMatch(string key, string dffm) {
    this->m_dffms.insert(
        pair<string, string>(key, dffm)
    );
}

/**
 * Returns a clone of the diffmatch patch
 * @return SanityPatchDiffMatchMutation* const
 */
SanityPartBuilder* SanityPatchDiffMatchMutation::clone() const {
    SanityPatchDiffMatchMutation* mut = new SanityPatchDiffMatchMutation();
    for(auto dfmp : this->m_dffms) {
        mut->AddDiffMatch(dfmp.first, dfmp.second);
    }
    return mut;
}

/**
 * Builds the patch
 * @return string
 */
string SanityPatchDiffMatchMutation::build() const {
    json patches;
    for(auto dfmp : this->m_dffms) {
        patches[dfmp.first] = dfmp.second;
    }

    json mut = {
        {"diffMatchPatch", patches}
    };

    return mut.dump();
}
