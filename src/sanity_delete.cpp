#include "sanity_delete.h"

SanityDelete::SanityDelete() {
    this->m_type = SanityPartBuilderType::DELETE;
}

SanityDelete::SanityDelete(string id)
    : SanityDelete() {
    this->m_id = id;
}

SanityDelete::SanityDelete(const SanityQuery& query)
    : SanityDelete() {
    this->m_query = (SanityQuery*)query.clone();
}

/**
 * Creates a clone of the delete mutation
 * @return SanityPartBuilder& const
 */
SanityPartBuilder* SanityDelete::clone() const {
    if(this->m_query != nullptr) {
        SanityDelete* del = new SanityDelete(*this->m_query);
        return del;
    }

    SanityDelete* del = new SanityDelete(this->m_id);
    return del;
}

/**
 * Builds the delete mutation
 * @return string const
 */
string SanityDelete::build() const {
    if(this->m_query != nullptr) {
        json mut = {
            {"delete", {
                {"query", this->m_query->build()}
            }}
        };
        return mut.dump();
    }

    json mut = {
        {"delete", {
            {"id", this->m_id}
        }}
    };
    return mut.dump();
}