#include "sanity_object.h"

SanityObject::SanityObject() {}

#pragma region getters
/**
 * Gets the id of the object
 * @return string
 */
string SanityObject::Id() const {
    return this->m_id;
}

/**
 * Gets the revision number of the obhect
 * @return string
 */
string SanityObject::Revision() const {
    return this->m_revision;
}

/**
 * Gets the type of the object
 * @return string
 */
string SanityObject::Type() const {
    return this->m_type;
}

/**
 * Gets the updated at datetime
 * @return tm
 */
tm SanityObject::UpdatedAt() const {
    return this->m_updated;
}

/**
 * Gets the created at datetime
 * @return tm
 */
tm SanityObject::CreatedAt() const {
    return this->m_created;
}
#pragma endregion

#pragma region setters
/**
 * Sets the object id
 * @param string id
 */
void SanityObject::SetId(string id) {
    this->m_id = id;
}

/**
 * Sets the object revision id
 * @param string rev
 */
void SanityObject::SetRevision(string rev) {
    this->m_revision = rev;
}

/**
 * Sets the object type
 * @param string type
 */
void SanityObject::SetType(string type) {
    this->m_type = type;
}

/**
 * Sets the updated at datetime
 * @param string updatedAt
 */
void SanityObject::SetUpdatedAt(string updatedAt) {
    int y,M,d,h,m;
    float s;
    sscanf(updatedAt.c_str(), "%d-%d-%dT%d:%d:%fZ", &y, &M, &d, &h, &m, &s);
    this->m_updated = {
        .tm_sec = (int)s,
        .tm_min = m,
        .tm_hour = h,
        .tm_mday = d,
        .tm_mon = M - 1,
        .tm_year = y
    };
}

/**
 * Sets the updated at datetime
 * @param tm updatedAt
 */
void SanityObject::SetUpdatedAt(tm updatedAt) {
    this->m_updated = updatedAt;
}

/**
 * Sets the created at datetime
 * @param string createdAt
 */
void SanityObject::SetCreatedAt(string createdAt) {
    int y,M,d,h,m;
    float s;
    sscanf(createdAt.c_str(), "%d-%d-%dT%d:%d:%fZ", &y, &M, &d, &h, &m, &s);
    this->m_created = {
        .tm_sec = (int)s,
        .tm_min = m,
        .tm_hour = h,
        .tm_mday = d,
        .tm_mon = M - 1,
        .tm_year = y - 1900
    };
}

/**
 * Sets the created at datetime
 * @param tm createdAt
 */
void SanityObject::SetCreatedAt(tm createdAt) {
    this->m_created = createdAt;
}
#pragma endregion
