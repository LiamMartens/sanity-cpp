#ifndef ISANITY_JSONSERIALIZABLE_H
#define ISANITY_JSONSERIALIZABLE_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ISanityJsonSerializable {
public:
    virtual json toJson() const { return json(); };
};

#endif // ISANITY_JSONSERIALIZABLE_H