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
public:
    SanityReference();
    SanityReference(json from);
    SanityReference(const SanityReference& ref);

    #pragma region getters
    string Type() const override;
    string Ref() const;
    #pragma endregion

    #pragma region setters
    void SetRef(string ref);
    #pragma endregion

    #pragma region overrides
    void Update(json from) override;
    json SharedJson() const override;
    json toJson() const override;
    json SaveObject() const override;
    SanityObject* clone() const override;
    #pragma endregion
};

#endif // SANITY_REFERENCE_H