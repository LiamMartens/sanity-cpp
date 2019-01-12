#include "sanity_patch_insert_mutation.h"

#pragma region SanityPatchInsertMutationItem
SanityPatchInsertMutationItem::SanityPatchInsertMutationItem(long value) {
    this->m_type = SanityPatchInsertMutationItemType::LONG;
    this->m_long_value = value;
}

SanityPatchInsertMutationItem::SanityPatchInsertMutationItem(double value) {
    this->m_type = SanityPatchInsertMutationItemType::DOUBLE;
    this->m_double_value = value;
}

SanityPatchInsertMutationItem::SanityPatchInsertMutationItem(string value) {
    this->m_type = SanityPatchInsertMutationItemType::STRING;
    this->m_string_value = value;
}

SanityPatchInsertMutationItem::SanityPatchInsertMutationItem(json value) {
    this->m_type = SanityPatchInsertMutationItemType::OBJECT;
    this->m_obj_value = value;
}

/**
 * Returns the value type
 * @return SanityPatchInsertMutationItemType const
 */
SanityPatchInsertMutationItemType SanityPatchInsertMutationItem::Type() const {
    return this->m_type;
}

/**
 * Returns the long value
 * @return long const
 */
long SanityPatchInsertMutationItem::LongValue() const {
    return this->m_long_value;
}

/**
 * Returns the double value
 * @return double const
 */
double SanityPatchInsertMutationItem::DoubleValue() const {
    return this->m_double_value;
}

/**
 * Returns the string value
 * @return string const
 */
string SanityPatchInsertMutationItem::StringValue() const {
    return this->m_string_value;
}

/**
 * Returns the json object value
 * @return json
 */
json SanityPatchInsertMutationItem::JsonValue() const {
    return this->m_obj_value;
}
#pragma endregion

#pragma region SanityPatchInsertMutation
SanityPatchInsertMutation::SanityPatchInsertMutation() {
    this->m_type = SanityPartBuilderType::PATCH_INSERT;
}

/**
 * Sets the after argument
 * @param string after
 */
void SanityPatchInsertMutation::SetAfter(string after) {
    this->m_after = after;
}

/**
 * Sets the before argument
 * @param string before
 */
void SanityPatchInsertMutation::SetBefore(string before) {
    this->m_before = before;
}

/**
 * Sets the before argument
 * @param string replace
 */
void SanityPatchInsertMutation::SetReplace(string replace) {
    this->m_replace = replace;
}

/**
 * Adds a long value
 * @param long value
 */
void SanityPatchInsertMutation::AddItem(long value) {
    SanityPatchInsertMutationItem item(value);
    this->m_items.push_back(item);
}

/**
 * Adds a double value
 * @param double value
 */
void SanityPatchInsertMutation::AddItem(double value) {
    SanityPatchInsertMutationItem item(value);
    this->m_items.push_back(item);
}

/**
 * Adds a string value
 * @param string value
 */
void SanityPatchInsertMutation::AddItem(string value) {
    SanityPatchInsertMutationItem item(value);
    this->m_items.push_back(item);
}

/**
 * Adds a json value
 * @param json value
 */
void SanityPatchInsertMutation::AddItem(json value) {
    SanityPatchInsertMutationItem item(value);
    this->m_items.push_back(item);
}

/**
 * Creates a clone of the insert mutation
 * @return SanityPatchInsertMutation*
 */
SanityPartBuilder* SanityPatchInsertMutation::clone() const {
    SanityPatchInsertMutation* mut = new SanityPatchInsertMutation();
    mut->SetAfter(this->m_after);
    mut->SetBefore(this->m_before);
    mut->SetReplace(this->m_replace);
    for(auto t : this->m_items) {
        switch(t.Type()) {
            case SanityPatchInsertMutationItemType::LONG:
                mut->AddItem(t.LongValue());
                break;
            case SanityPatchInsertMutationItemType::DOUBLE:
                mut->AddItem(t.DoubleValue());
                break;
            case SanityPatchInsertMutationItemType::STRING:
                mut->AddItem(t.StringValue());
                break;
            case SanityPatchInsertMutationItemType::OBJECT:
                mut->AddItem(t.JsonValue());
                break;
        }
    }
    return mut;
}

/**
 * Builds the patch mutation
 * @return string
 */
string SanityPatchInsertMutation::build() const {
    json items;
    for(auto t : this->m_items) {
        switch(t.Type()) {
            case SanityPatchInsertMutationItemType::LONG:
                items.push_back(t.LongValue());
                break;
            case SanityPatchInsertMutationItemType::DOUBLE:
                items.push_back(t.DoubleValue());
                break;
            case SanityPatchInsertMutationItemType::STRING:
                items.push_back(t.StringValue());
                break;
            case SanityPatchInsertMutationItemType::OBJECT:
                items.push_back(t.JsonValue());
                break;
        }
    }

    json params = {
        {"items", items}
    };
    if(!this->m_after.empty()) {
        params["after"] = this->m_after;
    } else if(!this->m_before.empty()) {
        params["before"] = this->m_before;
    } else if(!this->m_replace.empty()) {
        params["replace"] = this->m_replace;
    }

    json mut = {
        {"insert", params}
    };

    return mut.dump();
}
#pragma endregion