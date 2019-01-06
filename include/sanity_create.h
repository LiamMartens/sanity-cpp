#ifndef SANITY_CREATE_H
#define SANITY_CREATE_H

#include "sanity_part_builder.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

struct NoObjectException
    : public exception {
    const char* what() const throw() {
        return "No object set";
    }
};

class SanityCreate : public SanityPartBuilder {
private:
    /** @var Replace flag */
    bool m_replace = true;
    /** @var Object to create/replace */
    json m_object = nullptr;
public:
    #pragma region constructors
    SanityCreate(bool replace = true);
    SanityCreate(json object, bool replace = true);
    #pragma endregion

    void SetObject(json object);

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_CREATE_H