#ifndef SANITY_MUTATIONS_H
#define SANITY_MUTATIONS_H

#include <vector>
#include <nlohmann/json.hpp>
#include "sanity_part_builder.h"
#include "sanity_mutation.h"

using json = nlohmann::json;
using namespace std;

class SanityMutations : public SanityPartBuilder {
private:
    /** @var List of mutations */
    vector<SanityMutation*> m_mutations;
public:
    SanityMutations();

    void AddMutation(const SanityMutation& mut);

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_MUTATIONS_H