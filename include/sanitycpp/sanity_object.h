#ifndef SANITY_OBJECT_H
#define SANITY_OBJECT_H

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
using namespace std;

class SanityObject {
private:
    /** @var The id of the object */
    string m_id;
    /** @var The revision id */
    string m_revision;
    /** @var The type of the objet */
    string m_type;
    /** @var Updated at datetime */
    tm m_updated;
    /** @var Created at datetime */
    tm m_created;

public:
    SanityObject();
    SanityObject(json from);

    #pragma region getters
    string Id() const;
    string Revision() const;
    string Type() const;
    tm UpdatedAt() const;
    tm CreatedAt() const;
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
};

#endif // SANITY_OBJECT_H