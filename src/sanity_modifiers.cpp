#include "sanity_modifiers.h"

SanityModifiers::SanityModifiers() {
    this->m_type = SanityPartBuilderType::MODIFIERS;
}

SanityModifiers::~SanityModifiers() {
    while(!this->m_modifiers.empty()) {
        SanityModifier* mod = this->m_modifiers.back();
        delete mod;
        this->m_modifiers.pop_back();
    }
}

/**
 * Adds a modifier to the list
 * @param const SanityModifier& mod
 */
void SanityModifiers::AddModifier(const SanityModifier& mod) {
    SanityModifier* smod = (SanityModifier*)mod.clone();
    this->m_modifiers.push_back(smod);
}

/**
 * Clones the object
 * @return SanityPartBuilder*
 */
SanityPartBuilder* SanityModifiers::clone() const {
    SanityModifiers* mods_clone = new SanityModifiers();
    for(auto m : this->m_modifiers) {
        SanityModifier* m_clone = (SanityModifier*)m->clone();
        mods_clone->AddModifier(*m_clone);
    }
    return mods_clone;
}

/**
 * Builds the mods list
 * @return string
 */
string SanityModifiers::build() const {
    string built = "";
    for(auto m : this->m_modifiers) {
        if(!built.empty()) {
            built = built + " | ";
        }
        built = built + m->build();
    }
    return built;
}
