#ifndef SANITY_MUTATION_H
#define SANITY_MUTATION_H

#include <nlohmann/json.hpp>
#include "sanity_part_builder.h"

using json = nlohmann::json;

class SanityMutation : public SanityPartBuilder {
public:
    virtual json MutationObject() const {}
};

#endif // SANITY_MUTATION_H