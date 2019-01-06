#include "sanity_defined_filter.h"

SanityDefinedFilter::SanityDefinedFilter() {
    this->m_type = SanityPartBuilderType::DEFINED_FILTER;
}

SanityDefinedFilter::SanityDefinedFilter(string param) : SanityDefinedFilter() {
    this->m_param = param;
}

/**
 * Creates a clone of the defined filter
 * @return SanityPartBuildr* const
 */
SanityPartBuilder* SanityDefinedFilter::clone() const {
    return new SanityDefinedFilter(*this);
}

/**
 * Builds the is defined filter
 * @return string const
 */
string SanityDefinedFilter::build() const {
    return string(
        "defined(" +
        this->m_param +
        ")"
    );
}