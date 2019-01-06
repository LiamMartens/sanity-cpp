#include "sanity_boolean_filter.h"

using namespace std;

SanityBooleanFilter::SanityBooleanFilter() {
    this->m_type = SanityPartBuilderType::BOOLEAN_FILTER;
}

SanityBooleanFilter::SanityBooleanFilter(string name, bool truthy) : SanityBooleanFilter() {
    this->m_name = name;
    this->m_truthy = truthy;
}

/**
 * Creates a clone of the boolean filter
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityBooleanFilter::clone() const {
    return new SanityBooleanFilter(*this);
}

/**
 * Builds the boolean filter
 * @return string const
 */
string SanityBooleanFilter::build() const {
    char buff[this->m_name.size() + 1];
    sprintf(
        buff,
        "%s%s",
        this->m_truthy ? "" : "!",
        this->m_name.c_str()
    );
    return string(buff);
}
