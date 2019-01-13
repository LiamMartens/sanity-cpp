#ifndef SANITY_EQUALITY_FILTER_H
#define SANITY_EQUALITY_FILTER_H

#include <string>
#include "sanity_part_builder.h"

using namespace std;

enum SanityEqualityFilterCondition {
    EQ,
    LT,
    GT,
    LTEQ,
    GTEQ,
    NEQ
};

class SanityEqualityFilter : public SanityPartBuilder {
private:
    /** @var how to compare */
    SanityEqualityFilterCondition m_condition;
    /** @var left side of comparison */
    string m_left;
    /** @var right side of comparison */
    string m_right;

    SanityEqualityFilter();
public:
    SanityEqualityFilter(string left, SanityEqualityFilterCondition cond, string right);
    SanityEqualityFilter(const SanityEqualityFilter& filter);
    SanityEqualityFilter& operator=(const SanityEqualityFilter& filter) =default;
    string Left() const;
    SanityEqualityFilterCondition Condition() const;
    string Right() const;
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_EQUALITY_FILTER_H