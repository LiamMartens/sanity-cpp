#ifndef SANITY_DEFINED_FILTER_H
#define SANITY_DEFINED_FILTER_H

#include <string>
#include "sanity_part_builder.h"

using namespace std;

class SanityDefinedFilter : public SanityPartBuilder {
private:
    string m_param = "";

    SanityDefinedFilter();
public:
    SanityDefinedFilter(string param);
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_DEFINED_FILTER_H