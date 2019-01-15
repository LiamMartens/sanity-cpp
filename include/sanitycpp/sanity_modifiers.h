#ifndef SANITY_MODIFIERS_H
#define SANITY_MODIFIERS_H

#include <vector>
#include "sanity_modifier.h"
#include "sanity_part_builder.h"

using namespace std;

class SanityModifiers
    : public SanityPartBuilder {
private:
    /** @var List of modifiers */
    vector<SanityModifier*> m_modifiers;

public:
    SanityModifiers();

    void AddModifier(const SanityModifier& mod);

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_MODIFIERS_H