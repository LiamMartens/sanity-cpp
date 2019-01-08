#include "sanity_mutations.h"

SanityMutations::SanityMutations() {
    this->m_type = SanityPartBuilderType::MUTATIONS;
}

/**
 * Adds a mutation to the list
 * @param const SanityMutation& mut
 */
void SanityMutations::AddMutation(const SanityMutation& mut) {
    SanityMutation* smut = (SanityMutation*)mut.clone();
    this->m_mutations.push_back(smut);
}

/**
 * Clones the builder
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityMutations::clone() const {
    SanityMutations* muts_clone = new SanityMutations();
    for(auto m : this->m_mutations) {
        SanityMutation* m_clone = (SanityMutation*)m->clone();
        muts_clone->AddMutation(*m_clone);
    }
    return muts_clone;
}

/**
 * Builds the mutation list
 * @return string
 */
string SanityMutations::build() const {
    json list;
    for(auto m : this->m_mutations) {
        list.push_back(m->MutationObject());
    }
    json muts = {
        {"mutations", list}
    };
    return muts.dump();
}