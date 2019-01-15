#ifndef SANITY_BUILDER_H
#define SANITY_BUILDER_H

#include <string>

using namespace std;

enum class SanityPartBuilderType {
    BOOLEAN_FILTER = 1,
    DEFINED_FILTER,
    EQUALITY_FILTER,
    IN_FILTER,
    MATCH_FILTER,
    ORDER,
    PATH_PART,
    PATH,
    SLICE,
    SURL,
    OBJECT_PROJECTION,
    OBJECT_PROJECTION_PROPERTY,
    REFERENCES_FILTER,
    FILTER_PART,
    FILTER,
    QUERY,
    CONDITIONAL,
    SELECT,
    CREATE,
    DELETE,
    PATCH,
    PATCH_SET,
    PATCH_UNSET,
    PATCH_INSERT,
    PATCH_MATH,
    PATCH_DIFFMATCH,
    MUTATIONS,
    MODIFIERS,
};

class SanityPartBuilder {
protected:
    SanityPartBuilderType m_type;
public:
    virtual string build() const { return ""; }
    virtual SanityPartBuilder* clone() const { return new SanityPartBuilder(*this); }
    SanityPartBuilderType Type() { return this->m_type; }
};

#endif // SANITY_BUILDER_H