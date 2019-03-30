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

    this->Update(from);
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
 * @brief Gets the key of the object
 * @return string 
 */
string SanityObject::Key() const {
    return this->m_key;
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
    json o;
    if(!this->Id().empty()) {
        o["_id"] = this->Id();
    }
    if(!this->Key().empty()) {
        o["_key"] = this->Key();
    }
    if(!this->Type().empty()) {
        o["_type"] = this->Type();
    }
    if(!this->Revision().empty()) {
        o["_rev"] = this->Revision();
    }
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
 * @brief Sets the key
 * @param key 
 */
void SanityObject::SetKey(string key) {
    this->m_key = key;
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
    this->m_updated = SanityHelpers::TmFromString(updatedAt);
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
    this->m_created = SanityHelpers::TmFromString(createdAt);
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
 * @brief Finds reference data
 * 
 * @param client
 * @param key
 * @param is_array
 * @return true
 * @return false
 */
bool SanityObject::Join(const SanityClient& client, string key, bool is_array) {
    string id = this->Id();
    string type = this->Type();

    if(!id.empty() && !type.empty()) {
        SanityQuery query;
        // build and set filter
        SanityFilter filter;
        SanityEqualityFilter eqf_id("_id", SanityEqualityFilterCondition::EQ, SanityString::QuoteWrap(id));
        SanityEqualityFilter eqf_type("_type", SanityEqualityFilterCondition::EQ, SanityString::QuoteWrap(type));
        filter.AddPart(eqf_id);
        filter.AddPart(eqf_type, SanityFilterOperator::AND);
        query.SetFilter(filter);
        // build and set projection -> include joined key only
        SanityObjectProjection projection;
        SanityPath proj_path;
        if(is_array) {
            proj_path.AddArrayPart(key);
        } else {
            proj_path.AddPart(key);
        }
        SanityObjectProjection prop_subproj;
        SanityObjectProjectionProperty prop_subproj_restprop("...");
        prop_subproj.AddProperty(prop_subproj_restprop);
        proj_path.AddProjectionPart(prop_subproj);
        SanityObjectProjectionProperty prop_joined;
        prop_joined.SetValue(proj_path);
        prop_joined.SetRename(key);
        projection.AddProperty(prop_joined);
        query.SetProjection(projection);

        // perform  request
        SanityRequest* req = client.query(query);
        thread t = req->perform();
        t.join();
        json response = req->Response().ParsedBody;
        delete req;
        // check for results
        bool has_result = (response.find("result") != response.end());
        bool has_results = (response.find("results") != response.end());
        if(!has_result && !has_results) return false;
        map<json, bool> one_of_results = {
            {response["result"].get<json>(), has_result},
            {response["results"].get<json>(), has_results}
        };
        json results = SanityHelpers::OneOf<json>(one_of_results);
        if(results.empty()) return false;
        // update
        this->Update(results[0].get<json>());
        return true;
    } else if(id.empty()) {
        throw SanityObject_NoIdException();
    } else if(type.empty()) {
        throw SanityObject_NoTypeException();
    }

    return false;
}

/**
 * @brief Refreshes the object data
 *
 * @param client
 * @return true
 * @return false
 */
bool SanityObject::Refresh(const SanityClient& client) {
    string id = this->Id();
    string type = this->Type();

    if(!id.empty() && !type.empty()) {
        SanityQuery query;
        SanityFilter filter;
        SanityEqualityFilter eqf_id("_id", SanityEqualityFilterCondition::EQ, SanityString::QuoteWrap(id));
        SanityEqualityFilter eqf_type("_type", SanityEqualityFilterCondition::EQ, SanityString::QuoteWrap(type));
        filter.AddPart(eqf_id);
        filter.AddPart(eqf_type, SanityFilterOperator::AND);
        query.SetFilter(filter);

        // perform request
        SanityRequest* req = client.query(query);
        thread t = req->perform();
        t.join();
        json response = req->Response().ParsedBody;
        delete req;

        // check if anything was found
        bool has_result = (response.find("result") != response.end());
        bool has_results = (response.find("results") != response.end());
        if(!has_result && !has_results) return false;
        map<json, bool> one_of_results = {
            {response["result"].get<json>(), has_result},
            {response["results"].get<json>(), has_results}
        };
        json results = SanityHelpers::OneOf<json>(one_of_results);
        if(results.empty()) return false;

        // update object
        this->Update(results[0].get<json>());

        return true;
    } else if(id.empty()) {
        throw SanityObject_NoIdException();
    } else if(type.empty()) {
        throw SanityObject_NoTypeException();
    }

    return false;
}

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

        bool has_result = (resp.find("result") != resp.end());
        bool has_results = (resp.find("results") != resp.end());
        if(!has_result && !has_results) return false;
        map<json, bool> one_of_results = {
            {resp["result"].get<json>(), has_result},
            {resp["results"].get<json>(), has_results}
        };
        json results = SanityHelpers::OneOf<json>(one_of_results);
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

    if(this->Id().empty()) {
        throw SanityObject_NoIdException();
    }

    if(this->Type().empty()) {
        throw SanityObject_NoTypeException();
    }

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

    bool has_result = (resp.find("result") != resp.end());
    bool has_results = (resp.find("results") != resp.end());
    if(!has_result && !has_results) return false;
    map<json, bool> one_of_results = {
        {resp["result"].get<json>(), has_result},
        {resp["results"].get<json>(), has_results}
    };
    json results = SanityHelpers::OneOf<json>(one_of_results);

    if(results.empty()) {
        return false;
    }

    return true;
}
#pragma endregion

#pragma region
/**
 * @brief Updates the objects data using a JSON object
 * Does not update _id as this should only be updated explicitly
 * 
 * @param from
 */
void SanityObject::Update(json from) {
    json::iterator end = from.end();

    if(from.find("_rev") != end) {
        this->SetRevision(from["_rev"].get<string>());
    }

    if(from.find("_key") != end) {
        this->SetKey(from["_key"].get<string>());
    }

    if(from.find("_updatedAt") != end) {
        this->SetUpdatedAt(from["_updatedAt"].get<string>());
    }

    if(from.find("_createdAt") != end) {
        this->SetCreatedAt(from["_createdAt"].get<string>());
    }
}

/**
 * @brief Creates a json object
 * 
 * @return json
 */
json SanityObject::toJson() const {
    json o = this->SaveObject();

    tm updated_at = this->UpdatedAt();
    if(SanityHelpers::IsValidTm(updated_at)) {
        o["_updatedAt"] = SanityHelpers::TmToString(updated_at);
    }

    tm created_at = this->CreatedAt();
    if(SanityHelpers::IsValidTm(created_at)) {
        o["_createdAt"] = SanityHelpers::TmToString(created_at);
    }

    return o;
}

/**
 * @brief Clones the object
 * 
 * @return SanityObject*
 */
SanityObject* SanityObject::clone() const {
    SanityObject* cloned = new SanityObject(this->toJson());
    return cloned;
}
#pragma endregion
