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
#pragma endregion

#pragma region setters
/**
 * @brief Sets the ref
 * @param ref
 */
void SanityReference::SetRef(string ref) {
    this->m_ref = ref;
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
 * @brief Gets the shared json
 * 
 * @return json 
 */
json SanityReference::SharedJson() const {
    json obj = SanityObject::SharedJson();
    obj["_ref"] = this->Ref();
    return obj;
}

/**
 * @brief Converts the ref to json
 * 
 * @return json
 */
json SanityReference::toJson() const {
    json o = SanityObject::toJson();
    return o;
}

/**
 * @brief Gets the saveable object
 * 
 * @return json
 */
json SanityReference::SaveObject() const {
    json o = SanityObject::SaveObject();
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
