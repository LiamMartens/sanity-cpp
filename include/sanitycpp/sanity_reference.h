#ifndef SANITY_REFERENCE_H
#define SANITY_REFERENCE_H

#include <string>
#include <nlohmann/json.hpp>
#include "sanity_object.h"

using json = nlohmann::json;
using namespace std;

class SanityReference
    : public SanityObject {
private:
    /** @var The reference */
    string m_ref;
    /** @var The ref key for arrays */
    string m_key;
public:
    SanityReference();
    SanityReference(json from);

    #pragma region getters
    string Ref() const;
    string Key() const;
    json SaveObject() const override;
    #pragma endregion

    #pragma region setters
    void SetRef(string ref);
    void SetKey(string key);
    #pragma endregion
};

#endif // SANITY_REFERENCE_H