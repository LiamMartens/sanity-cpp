#include "sanity_patch.h"

#pragma region constructors
SanityPatch::SanityPatch() {
    this->m_type = SanityPartBuilderType::PATCH;
}

SanityPatch::SanityPatch(string id)
    : SanityPatch() {
    this->m_id = id;
}

SanityPatch::SanityPatch(const SanityQuery& query)
    : SanityPatch() {
    this->m_query = (SanityQuery*)query.clone();
}

SanityPatch::~SanityPatch() {
    if(this->m_query != nullptr) {
        delete this->m_query;
    }

    while(!this->m_patches.empty()) {
        SanityPatchMutation* mut = this->m_patches.back();
        delete mut;
        this->m_patches.pop_back();
    }
}
#pragma endregion

/**
 * Sets the revision id
 * @param string id
 */
void SanityPatch::SetRevisionId(string id) {
    this->m_revision_id = id;
}

/**
 * Adds a patch
 * @param const SanityPatchMutation& patch
 */
void SanityPatch::AddPatch(const SanityPatchMutation& patch) {
    SanityPatchMutation* mut = (SanityPatchMutation*)patch.clone();
    this->m_patches.push_back(mut);
}

/**
 * Gets the json mutation object
 * @return json const
 */
json SanityPatch::MutationObject() const {
    json data;

    if(!this->m_id.empty()) {
        data["id"] = this->m_id;
    } else if(this->m_query != nullptr) {
        data["query"] = this->m_query->build();
    }

    for(auto p : this->m_patches) {
        json o = json::parse(p->build());
        data.merge_patch(o);
    }

    json mut = {
        {"patch", data}
    };

    return mut;
}

/**
 * Creates a clone of the patch mutation
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityPatch::clone() const {
    SanityPatch* patch;
    if(this->m_query == nullptr) {
        patch = new SanityPatch(this->m_id);
    } else {
        patch = new SanityPatch(*this->m_query);
    }
    patch->SetRevisionId(this->m_revision_id);
    for(auto p : this->m_patches) {
        SanityPatchMutation* p_clone = (SanityPatchMutation*)p->clone();
        patch->AddPatch(*p_clone);
    }
    return patch;
}

/**
 * Builds the patch
 * @return string
 */
string SanityPatch::build() const {
    json mut = this->MutationObject();
    return mut.dump();
}
