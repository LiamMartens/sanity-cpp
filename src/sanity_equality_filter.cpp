#include "sanity_equality_filter.h"

SanityEqualityFilter::SanityEqualityFilter() {
    this->m_type = SanityPartBuilderType::EQUALITY_FILTER;
}

SanityEqualityFilter::SanityEqualityFilter(string left, SanityEqualityFilterCondition cond, string right)
    : SanityEqualityFilter() {
    this->m_left = left;
    this->m_condition = cond;
    this->m_right = right;
}

SanityEqualityFilter::SanityEqualityFilter(const SanityEqualityFilter& filter)
    : SanityEqualityFilter(filter.Left(), filter.Condition(), filter.Right()) {
}

/**
 * Gets the lefthand of the equality
 * @return string const
 */
string SanityEqualityFilter::Left() const {
    return string(this->m_left);
}

/**
 * Gets the condition of the equality
 * @return SanityEqualityFilterCondition const
 */
SanityEqualityFilterCondition SanityEqualityFilter::Condition() const {
    return this->m_condition;
}

/**
 * Gets the righthand of the equality
 * @return string const
 */
string SanityEqualityFilter::Right() const {
    return string(this->m_right);
}

/**
 * Creates a clone of the object
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityEqualityFilter::clone() const {
    return new SanityEqualityFilter(*this);
}

/**
 * Builds the equality filter
 * @return string const
 */
string SanityEqualityFilter::build() const {
    string cond;
    switch(this->m_condition) {
        case SanityEqualityFilterCondition::EQ:
            cond = "==";
            break;
        case SanityEqualityFilterCondition::LT:
            cond = "<";
            break;
        case SanityEqualityFilterCondition::GT:
            cond = ">";
            break;
        case SanityEqualityFilterCondition::LTEQ:
            cond = "<=";
            break;
        case SanityEqualityFilterCondition::GTEQ:
            cond = ">=";
            break;
        case SanityEqualityFilterCondition::NEQ:
            cond = "!=";
            break;
    }

    unsigned int filter_size = (sizeof this->m_left) + (sizeof this->m_right) + (sizeof cond) + 2;
    char buff[filter_size];
    sprintf(
        buff,
        "%s %s %s",
        this->m_left.c_str(),
        cond.c_str(),
        this->m_right.c_str()
    );

    return string(buff);
}
