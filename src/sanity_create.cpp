#include "sanity_create.h"

#pragma region constructors
SanityCreate::SanityCreate(bool replace) {
    this->m_type = SanityPartBuilderType::CREATE;
    this->m_replace = replace;
}

SanityCreate::SanityCreate(json object, bool replace)
    : SanityCreate() {
    this->m_object = object;
}
#pragma endregion

/**
 * Sets the object
 * @param json object
 */
void SanityCreate::SetObject(json object) {
    this->m_object = object;
}

/**
 * Creates a clone of the create object
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityCreate::clone() const {
    SanityCreate* cloned = new SanityCreate(this->m_object, this->m_replace);
    return cloned;
}

/**
 * Builds the mutation
 * @return string const
 */
string SanityCreate::build() const {
    if(this->m_object != nullptr) {
        string cmd = this->m_replace ? "createOrReplace" : "createIfNotExists";
        return "{\"" + cmd + "\":" + this->m_object.dump() + "}";
    }

    throw NoObjectException();
}