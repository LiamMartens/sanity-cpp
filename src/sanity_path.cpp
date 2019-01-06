#include "sanity_path.h"

#pragma region SanityPathPart
SanityPathPart::SanityPathPart() {
    this->m_type = SanityPartBuilderType::PATH_PART;
}

SanityPathPart::SanityPathPart(string part) : SanityPathPart() {
    this->m_part = part;
}

SanityPathPart::SanityPathPart(const SanityPathPart& part) : SanityPathPart() {
    string p = part.Part();
    this->m_part = p;
}

/**
 * Creates a clone of the path part
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityPathPart::clone() const {
    return new SanityPathPart(*this);
}

/**
 * Default part build
 * @return string const
 */
string SanityPathPart::Part() const {
    return string(this->m_part);
}
#pragma endregion

#pragma region SanityPathArrayPart
/**
 * Creates a clone of the array part
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityPathArrayPart::clone() const {
    return new SanityPathArrayPart(*this);
}

/**
 * Builds the array type part
 * @return string const
 */
string SanityPathArrayPart::build() const {
    return string(this->m_part + "[]");
}
#pragma endregion

#pragma region SanityPathPropertyPart
/**
 * Creates a clone of the property part
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityPathPropertyPart::clone() const {
    return new SanityPathPropertyPart(*this);
}

/**
 * Builds the property type part
 * @return string const
 */
string SanityPathPropertyPart::build() const {
    return string(this->m_part);
}
#pragma endregion

#pragma region SanityPath
SanityPath::SanityPath() {
    this->m_type = SanityPartBuilderType::PATH;
}

/**
 * Adds a property type part to the path
 * @param string path The part to add
 */
void SanityPath::AddPart(string part) {
    SanityPathPropertyPart* p = new SanityPathPropertyPart(part);
    this->m_parts.push_back(p);
}

/**
 * Adds an array type part to the path
 * @param string part The part to add
 */
void SanityPath::AddArrayPart(string part) {
    SanityPathArrayPart* p = new SanityPathArrayPart(part);
    this->m_parts.push_back(p);
}

/**
 * Adds a projection to the path
 * @param const SanityObjectProjection& projection The projection to add
 */
void SanityPath::AddProjectionPart(const SanityObjectProjection& projection) {
    SanityObjectProjection* p = new SanityObjectProjection(projection);
    this->m_parts.push_back(p);
}

/**
 * Resets the path
 */
void SanityPath::Reset() {
    this->m_parts.clear();
}

/**
 * Creates a clone of the path object
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityPath::clone() const {
    return new SanityPath(*this);
}

/**
 * Builds the complete path
 * @return string const
 */
string SanityPath::build() const {
    string path = "";
    for(auto part : this->m_parts) {
        if(!path.empty()) {
            if(part->Type() == SanityPartBuilderType::OBJECT_PROJECTION) {
                path = path + "->";
            } else {
                path = path + ".";
            }
        }
        path = path + part->build();
    }
    return path;
}
#pragma endregion
