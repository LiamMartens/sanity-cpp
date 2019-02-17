#ifndef SANITY_OBJECT_H
#define SANITY_OBJECT_H

#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
#include "sanity_client.h"
#include "sanity_modifiers.h"
#include "sanity_slice.h"
#include "sanity_delete.h"
#include "sanity_patch.h"
#include "sanity_patch_set_mutation.h"
#include "sanity_mutations.h"
#include "sanity_path.h"
#include "sanity_equality_filter.h"
#include "sanity_object_projection.h"
#include "sanity_helpers.h"
#include "isanity_cloneable.h"
#include "isanity_jsonserializable.h"
#include "isanity_jsonupdateable.h"

using json = nlohmann::json;
using namespace std;

class SanityObject_NoResultException
    : public exception {
    const char* what() const throw() {
        return "No result";
    }
};

class SanityObject_NoIdException
    : public exception {
    const char* what() const throw() {
        return "No ID";
    }
};

class SanityObject_NoTypeException
    : public exception {
    const char* what() const throw() {
        return "No type";
    }
};

class SanityObject :
    public ISanityCloneable,
    public ISanityJsonSerializable,
    public ISanityJsonUpdateable {
private:
    /** @var The id of the object */
    string m_id;
    /** @var The revision id */
    string m_revision;
    /** @var The type of the objet */
    string m_type;
    /** @var Updated at datetime */
    tm m_updated = { -1901, -1, 0, -1, -1, -1 };
    /** @var Created at datetime */
    tm m_created = { -1901, -1, 0, -1, -1, -1 };

public:
    #pragma region templated
    /**
     * Finds sanity objects by query
     * @param const SanityClient& client
     * @param SanityQuery query
     * @return vector<SanityObject>
     */
    template<typename T>
    static vector<T> FindByQuery(const SanityClient& client, SanityQuery query) {
        SanityRequest* request = client.query(query);
        thread t = request->perform();
        t.join();

        vector<T> objects_vec;
        json response = request->Response().ParsedBody;
        if(response.find("result") != response.end()) {
            json results = response["result"].get<json>();
            size_t num_results = results.size();
            for(auto& o_item : results) {
                json o = o_item.get<json>();
                objects_vec.push_back(T(o));
            }
        }

        return objects_vec;
    };

    /**
     * @brief Finds the first object by query
     * 
     * @tparam T Return type of the request
     * @param client The client to use
     * @param query The query to use (sice will be injected)
     * @return T 
     */
    template<typename T>
    static T FindFirstByQuery(const SanityClient& client, SanityQuery query) {
        /* clones the query and injects slice into modifiers */
        SanityQuery query_clone = query;
        SanityModifiers modifiers = query_clone.Modifiers();
        SanitySlice slice(0);
        modifiers.AddModifier(slice);
        query_clone.SetModifiers(modifiers);

        /* perform request */
        SanityRequest* request = client.query(query_clone);
        thread t = request->perform();
        t.join();

        json response = request->Response().ParsedBody;
        if(response.find("result") == response.end()) {
            throw SanityObject_NoResultException();
        }

        json result = response["result"];
        if(result.is_null()) {
            throw SanityObject_NoResultException();
        }
        T resp = T(result.get<json>());
        return resp;
    };
    #pragma endregion

    SanityObject(string override_type = "");
    SanityObject(json from, string override_type = "");

    #pragma region getters
    string Id() const;
    string Revision() const;
    virtual string Type() const;
    tm UpdatedAt() const;
    tm CreatedAt() const;
    virtual json SaveObject() const;
    #pragma endregion

    #pragma region setters
    void SetId(string id);
    void SetRevision(string rev);
    void SetType(string type);
    void SetUpdatedAt(string updatedAt);
    void SetUpdatedAt(tm updatedAt);
    void SetCreatedAt(string createdAt);
    void SetCreatedAt(tm createdAt);
    #pragma endregion

    #pragma region queries
    bool Join(const SanityClient& client, string key, bool is_array = false);
    bool Refresh(const SanityClient& client);
    bool Delete(const SanityClient& client);
    bool Save(const SanityClient& client);
    #pragma endregion

    #pragma region overrides
    virtual void Update(json from) override;
    virtual json toJson() const override;
    virtual SanityObject* clone() const override;
    #pragma endregion
};

#endif // SANITY_OBJECT_H