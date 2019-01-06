#ifndef SANITY_BOOLEAN_FILTER_H
#define SANITY_BOOLEAN_FILTER_H

#include <string>
#include "sanity_part_builder.h"

using namespace std;

class SanityBooleanFilter : public SanityPartBuilder {
private:
    /** @var name of the parameter */
    string m_name = "";
    /** @var whether to check for truthy or falsey */
    bool m_truthy = true;

    SanityBooleanFilter();

public:
    SanityBooleanFilter(string name, bool truthy = true);
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_BOOLEAN_FILTER_H