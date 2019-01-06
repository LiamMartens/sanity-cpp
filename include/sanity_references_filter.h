#ifndef SANITY_REFERENCES_FILTER_H
#define SANITY_REFERENCES_FILTER_H

#include <string>
#include "sanity_part_builder.h"

using namespace std;

class SanityReferencesFilter : SanityPartBuilder {
private:
    string m_name = "";
public:
    SanityReferencesFilter(string name);
    string build() const override;
};

#endif // SANITY_REFERENCES_FILTER_H