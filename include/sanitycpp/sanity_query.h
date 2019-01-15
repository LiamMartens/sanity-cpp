#ifndef SANITY_QUERY_H
#define SANITY_QUERY_H

#include "sanity_filter.h"
#include "sanity_modifiers.h"
#include "sanity_part_builder.h"
#include "sanity_object_projection.h"
#include <string>
#include <vector>

using namespace std;

class SanityObjectProjection;

class SanityQuery : public SanityPartBuilder {
private:
    /** @var The filter to use */
    SanityFilter* m_filter = nullptr;
    /** @var The object projection attached to the query */
    SanityObjectProjection* m_projection = nullptr;
    /** @var Modifiers */
    SanityModifiers* m_modifiers = nullptr;

public:
    #pragma region constructors
    SanityQuery();
    SanityQuery(const SanityQuery& query);
    SanityQuery& operator=(const SanityQuery& query) =default;
    ~SanityQuery();
    #pragma endregion

    #pragma region setters
    void SetFilter(const SanityFilter& filter);
    void SetProjection(const SanityObjectProjection& projection);
    void SetModifiers(const SanityModifiers& modifiers);
    #pragma endregion

    #pragma region getters
    SanityFilter Filter() const;
    SanityObjectProjection Projection() const;
    SanityModifiers Modifiers() const;
    #pragma endregion

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_QUERY_H