#ifndef SANITY_FILTER_H
#define SANITY_FILTER_H

#include <string>
#include <vector>
#include "sanity_part_builder.h"

using namespace std;

enum SanityFilterOperator {
    NONE,
    AND,
    OR
};

class SanityFilterPart : public SanityPartBuilder {
private:
    /** @var The operator to connect the part */
    SanityFilterOperator m_op = SanityFilterOperator::NONE;
    /** @var Part builder */
    SanityPartBuilder* m_builder;

    SanityFilterPart();
public:
    SanityFilterPart(const SanityPartBuilder& builder);
    SanityFilterPart(const SanityPartBuilder& builder, SanityFilterOperator op);
    SanityFilterPart(const SanityFilterPart& part);
    SanityFilterPart& operator=(const SanityFilterPart& part) =default;
    ~SanityFilterPart();
    SanityPartBuilder* clone() const override;
    string build() const override;
};

class SanityFilter : public SanityPartBuilder {
private:
    vector<SanityFilterPart*> m_parts;
public:
    SanityFilter();
    SanityFilter(const SanityFilter& filter);
    SanityFilter& operator=(const SanityFilter& filter) =default;
    ~SanityFilter();
    void AddPart(const SanityPartBuilder& builder, SanityFilterOperator op = SanityFilterOperator::NONE);
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_FILTER_H