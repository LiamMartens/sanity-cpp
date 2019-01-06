#include "sanity_references_filter.h"

SanityReferencesFilter::SanityReferencesFilter(string name) {
    this->m_type = SanityPartBuilderType::REFERENCES_FILTER;
    this->m_name = name;
}

/**
 * Builds the references filter
 * @return string const
 */
string SanityReferencesFilter::build() const {
    return "references(" + this->m_name + ")";
}