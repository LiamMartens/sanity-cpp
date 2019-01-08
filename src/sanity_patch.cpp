#include "sanity_patch.h"

SanityPatch::SanityPatch(json data) {
    this->m_type = SanityPartBuilderType::PATCH;
    this->m_data = data;
}

SanityPatch::SanityPatch(const SanityPatch& path) {
    this->m_data = path.m_data;
}

/**
 * Sets the patch revision id check
 * @param string id
 */
void SanityPatch::SetRevisionId(string id) {
    this->m_revision_id = id;
}

/**
 * Sets the patch query param
 * @param const SanityQuery& query
 */
void SanityPatch::SetQuery(const SanityQuery& query) {
    this->m_query = (SanityQuery*)query.clone();
}

/**
 * Returns the full mutation object
 * @return json
 */
json SanityPatch::MutationObject() const {
    json body = this->m_data;
    if(!this->m_revision_id.empty()) {
        body["ifRevisionID"] = this->m_revision_id;
    }
    if(this->m_query != nullptr) {
        body["query"] = this->m_query->build();
    }

    json obj = {
        {"patch", body}
    };

    return obj;
}

/**
 * Creates a clone of the patch mutation object
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityPatch::clone() const {
    SanityPatch* p = new SanityPatch(this->m_data);
    p->SetRevisionId(this->m_revision_id);
    SanityQuery* query_clone = (SanityQuery*)this->m_query->clone();
    p->SetQuery(*query_clone);
    return p;
}

/**
 * Builds the patch mutation
 * @return string const
 */
string SanityPatch::build() const {
    json obj = this->MutationObject();
    return obj.dump();
}
