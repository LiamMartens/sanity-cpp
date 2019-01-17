#include "sanity_object.h"

SanityObject::SanityObject(string override_type) {
    this->m_type = override_type;
}

SanityObject::SanityObject(json from, string override_type)
    : SanityObject(override_type) {
    json::iterator end = from.end();

    if(from.find("_id") != end) {
        this->SetId(from["_id"].get<string>());
    }

    string derivedType = this->Type();
    bool derivedTypeIsEmpty = derivedType.empty();
    if(derivedTypeIsEmpty && from.find("_type") != end) {
        this->SetType(from["_type"].get<string>());
    } else if(!derivedTypeIsEmpty) {
        this->SetType(derivedType);
    }

    if(from.find("_rev") != end) {
        this->SetRevision(from["_rev"].get<string>());
    }

    if(from.find("_updatedAt") != end) {
        this->SetUpdatedAt(from["_updatedAt"].get<string>());
    }

    if(from.find("_createdAt") != end) {
        this->SetCreatedAt(from["_createdAt"].get<string>());
    }
}

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

/**
 * @brief The object to use when saving
 * 
 * @return json 
 */
json SanityObject::SaveObject() const {
    json o = {
        {"_id", this->m_id},
        {"_type", this->m_type}
    };
    return o;
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

#pragma region mutations
/**
 * @brief Deletes the object in Sanity
 * 
 * @return true 
 * @return false 
 */
bool SanityObject::Delete(const SanityClient& client) {
    if(!this->m_id.empty()) {
        SanityMutations mutations;
        SanityDelete del(this->m_id);
        mutations.AddMutation(del);
        SanityRequest* req = client.mutate(mutations);
        thread t = req->perform();
        t.join();
        json resp = req->Response().ParsedBody;
        delete req;

        if(resp.find("results") == resp.end()) {
            return false;
        }

        json results = resp["results"].get<json>();
        if(results.empty()) {
            return false;
        }

        return true;
    }

    throw SanityObject_NoIdException();
}

/**
 * @brief Saves the object params (requires ID)
 * 
 * @param client 
 * @return true 
 * @return false 
 */
bool SanityObject::Save(const SanityClient& client) {
    json object = this->SaveObject();
    SanityMutations mutations;
    // try to create if not exists yet
    SanityCreate create(object, false);
    mutations.AddMutation(create);
    // try to update
    SanityPatch patches(this->Id());
    SanityPatchSetMutation set_patch(object);
    patches.AddPatch(set_patch);
    mutations.AddMutation(patches);
    // perform request
    SanityRequest* request = client.mutate(mutations);
    thread t = request->perform();
    t.join();
    json resp = request->Response().ParsedBody;
    delete request;

    if(resp.find("results") == resp.end()) {
        return false;
    }

    json results = resp["results"].get<json>();
    if(results.empty()) {
        return false;
    }

    return true;
}
#pragma endregion
