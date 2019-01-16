#include "sanity_query.h"

#pragma region constructors
SanityQuery::SanityQuery() {
    this->m_type = SanityPartBuilderType::QUERY;
}

SanityQuery::SanityQuery(const SanityQuery& query) {
    if(query.m_filter != nullptr) {
        this->SetFilter(*query.m_filter);
    }

    if(query.m_modifiers != nullptr) {
        this->SetModifiers(*query.m_modifiers);
    }

    if(query.m_projection != nullptr) {
        this->SetProjection(*query.m_projection);
    }
}

SanityQuery::~SanityQuery() {
    if(this->m_filter != nullptr) {
        delete this->m_filter;
    }

    if(this->m_projection != nullptr) {
        delete this->m_projection;
    }
}
#pragma endregion

#pragma region setters
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
 * Sets the modifiers to use
 * @param const SanityModifeirs& modifiers
 */
void SanityQuery::SetModifiers(const SanityModifiers& modifiers) {
    this->m_modifiers = (SanityModifiers*)modifiers.clone();
}
#pragma endregion

#pragma region getters
/**
 * @brief Returns the current filter or an empty filter
 * if no filter has been set
 * 
 * @return SanityFilter 
 */
SanityFilter SanityQuery::Filter() const {
    if(this->m_filter != nullptr) {
        SanityFilter* filter = (SanityFilter*)this->m_filter->clone();
        return *filter;
    }

    return SanityFilter();
}

/**
 * @brief Gets the current projection or empty if none set
 * 
 * @return SanityObjectProjection 
 */
SanityObjectProjection SanityQuery::Projection() const {
    if(this->m_projection != nullptr) {
        SanityObjectProjection* projection = (SanityObjectProjection*)this->m_projection->clone();
        return *projection;
    }

    return SanityObjectProjection();
}

/**
 * @brief Gets the current modifiers or empty if none set
 * 
 * @return SanityModifiers 
 */
SanityModifiers SanityQuery::Modifiers() const {
    if(this->m_modifiers != nullptr) {
        SanityModifiers* modifiers = (SanityModifiers*)this->m_modifiers->clone();
        return *modifiers;
    }

    return SanityModifiers();
}
#pragma endregion

/**
 * Clones the query
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityQuery::clone() const {
    SanityQuery* q = new SanityQuery();

    if(this->m_filter != nullptr) {
        q->SetFilter(*this->m_filter);
    }

    if(this->m_modifiers != nullptr) {
        q->SetModifiers(*this->m_modifiers);
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

    if(this->m_modifiers != nullptr) {
        build = build + "|" + this->m_modifiers->build();
    }

    if(this->m_projection != nullptr) {
        build = build + this->m_projection->build();
    }

    return build;
}
