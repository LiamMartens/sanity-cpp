#include "sanity_reference.h"

SanityReference::SanityReference() : SanityObject(this->Type()) {}
SanityReference::SanityReference(json from) : SanityObject(from, this->Type()) {
    this->Update(from);
}
SanityReference::SanityReference(const SanityReference& ref) : SanityReference(ref.toJson()) {}

#pragma region getters
/**
 * @brief Enforced type
 * 
 * @return string 
 */
string SanityReference::Type() const {
    return "reference";
}

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

#pragma region overrides
/**
 * @brief Updates the object from json
 * 
 * @param from
 */
void SanityReference::Update(json from) {
    json::iterator end = from.end();

    if(from.find("_key") != end) {
        this->SetKey(from["_key"].get<string>());
    }

    if(from.find("_ref") != end) {
        this->SetRef(from["_ref"].get<string>());
    }
}

/**
 * @brief Converts the ref to json
 * 
 * @return json
 */
json SanityReference::toJson() const {
    json o = SanityObject::toJson();
    o["_ref"] = this->Ref();
    if(!this->Key().empty()) {
        o["_key"] = this->Key();
    }
    return o;
}

/**
 * @brief Creates a clone of the object
 * 
 * @return SanityObject*
 */
SanityObject* SanityReference::clone() const {
    SanityReference* ref = new SanityReference(this->toJson());
    return ref;
}
#pragma endregion
