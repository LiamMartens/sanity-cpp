#ifndef SANITY_DELETE_H
#define SANITY_DELETE_H

#include "sanity_query.h"
#include "sanity_mutation.h"
#include "sanity_part_builder.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class SanityDelete : public SanityMutation {
private:
    /** @var The id to delete */
    string m_id;
    /**
     * @var The query to delete
     * Should not include a projection, just a filter
     */
    SanityQuery* m_query = nullptr;

    SanityDelete();
public:
    #pragma region constructors
    SanityDelete(string id);
    SanityDelete(const SanityQuery& query);
    ~SanityDelete();
    #pragma endregion

    json MutationObject() const override;
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_DELETE_H