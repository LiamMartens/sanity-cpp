#ifndef SANITY_DELETE_H
#define SANITY_DELETE_H

#include "sanity_query.h"
#include "sanity_part_builder.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class SanityDelete : public SanityPartBuilder {
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
    SanityDelete(string id);
    SanityDelete(const SanityQuery& query);

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_DELETE_H