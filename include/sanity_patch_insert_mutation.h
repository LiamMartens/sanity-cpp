#ifndef SANITY_PATCH_INSERT_MUTATION_H
#define SANITY_PATCH_INSERT_MUTATION_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "sanity_patch_mutation.h"

using json = nlohmann::json;
using namespace std;

enum class SanityPatchInsertMutationItemType {
    LONG,
    DOUBLE,
    STRING,
    OBJECT
};

class SanityPatchInsertMutationItem {
private:
    /** @var The type of the value */
    SanityPatchInsertMutationItemType m_type;

    /** @var long value type */
    long m_long_value;
    /** @var double value type */
    double m_double_value;
    /** @var string value type */
    string m_string_value;
    /** @var json data type */
    json m_obj_value;
public:
    SanityPatchInsertMutationItem(long value);
    SanityPatchInsertMutationItem(double value);
    SanityPatchInsertMutationItem(string value);
    SanityPatchInsertMutationItem(json value);

    SanityPatchInsertMutationItemType Type() const;
    long LongValue() const;
    double DoubleValue() const;
    string StringValue() const;
    json JsonValue() const;
};

class SanityPatchInsertMutation : public SanityPatchMutation {
private:
    /** @var after argument */
    string m_after;
    /** @var before argument */
    string m_before;
    /** @var replace argument */
    string m_replace;

    /** @var items to insert */
    vector<SanityPatchInsertMutationItem> m_items;
public:
    SanityPatchInsertMutation();

    void SetAfter(string after);
    void SetBefore(string before);
    void SetReplace(string replace);

    void AddItem(long value);
    void AddItem(double value);
    void AddItem(string value);
    void AddItem(json value);

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_PATCH_INSERT_MUTATION_H