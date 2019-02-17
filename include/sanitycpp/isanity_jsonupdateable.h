#ifndef ISANITY_JSONUPDATEABLE_H
#define ISANITY_JSONUPDATEABLE_H

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ISanityJsonUpdateable {
public:
    virtual void Update(json from) {};
};

#endif // ISANITY_JSONUPDATEABLE_H