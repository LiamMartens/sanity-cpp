#include "sanity_query.h"

SanityQuery::SanityQuery() {
    this->m_type = SanityPartBuilderType::QUERY;
}

SanityQuery::~SanityQuery() {
    if(this->m_filter != nullptr) {
        delete this->m_filter;
    }

    if(this->m_projection != nullptr) {
        delete this->m_projection;
    }
}

SanityQuery::SanityQuery(const SanityQuery& query) {
    if(query.m_filter != nullptr) {
        this->SetFilter(*query.m_filter);
    }

    if(query.m_projection != nullptr) {
        this->SetProjection(*query.m_projection);
    }
}

/**
 * Sets the filter
 * @param SanityFilter* filter The filter to use
 */
void SanityQuery::SetFilter(const SanityFilter& filter) {
    this->m_filter = (SanityFilter*)filter.clone();
}

/**
 * Sets the projection to use
 * @param SanityObjectProjection* projection The projection to use
 */
void SanityQuery::SetProjection(const SanityObjectProjection& projection) {
    this->m_projection = (SanityObjectProjection*)projection.clone();
}

/**
 * Clones the query
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityQuery::clone() const {
    SanityQuery* q = new SanityQuery();

    if(this->m_filter != nullptr) {
        q->SetFilter(*this->m_filter);
    }

    if(this->m_projection != nullptr) {
        q->SetProjection(*this->m_projection);
    }

    return q;
}

/**
 * Builds the query
 * @return string const
 */
string SanityQuery::build() const {
    string build = "";
    if(this->m_filter != nullptr) {
        build = "*[" + this->m_filter->build() + "]";
    }

    if(this->m_projection != nullptr) {
        build = build + this->m_projection->build();
    }

    return build;
}
