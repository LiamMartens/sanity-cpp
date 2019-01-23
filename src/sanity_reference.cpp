#include "sanity_reference.h"

SanityReference::SanityReference() {
    this->SetType("reference");
}

SanityReference::SanityReference(json from) : SanityObject(from) {
    json::iterator end = from.end();

    if(from.find("_key") != end) {
        this->SetKey(from["_key"].get<string>());
    }

    if(from.find("_ref") != end) {
        this->SetRef(from["_ref"].get<string>());
    }
}

#pragma region getters
/**
 * @brief Gets the ref
 * @return string
 */
string SanityReference::Ref() const {
    return this->m_ref;
}

/**
 * @brief Gets the array key
 * @return string
 */
string SanityReference::Key() const {
    return this->m_key;
}

/**
 * @brief Gets the save object
 * @return json
 */
json SanityReference::SaveObject() const {
    json obj = {
        {"_type", this->Type()},
        {"_ref", this->Ref()}
    };

    if(!this->Key().empty()) {
        obj["_key"] = this->Key();
    }

    return obj;
}
#pragma endregion

#pragma region setters
/**
 * @brief Sets the ref
 * @param ref
 */
void SanityReference::SetRef(string ref) {
    this->m_ref = ref;
}

/**
 * @brief Sets the key
 * @param key
 */
void SanityReference::SetKey(string key) {
    this->m_key = key;
}
#pragma endregion


