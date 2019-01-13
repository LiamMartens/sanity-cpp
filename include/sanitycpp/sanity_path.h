#ifndef SANITY_PATH_H
#define SANITY_PATH_H

#include <string>
#include <vector>
#include "sanity_part_builder.h"
#include "sanity_object_projection.h"

using namespace std;

class SanityObjectProjection;

class SanityPathPart : public SanityPartBuilder {
protected:
    string m_part = "";
    SanityPathPart();
public:
    SanityPathPart(string part);
    SanityPathPart(const SanityPathPart& part);
    SanityPathPart& operator=(const SanityPathPart& part) =default;
    virtual SanityPartBuilder* clone() const override;
    string Part() const;
};

class SanityPathArrayPart : public SanityPathPart {
    using SanityPathPart::SanityPathPart;
public:
    SanityPartBuilder* clone() const override;
    string build() const override;
};

class SanityPathPropertyPart : public SanityPathPart {
    using SanityPathPart::SanityPathPart;
public:
    SanityPartBuilder* clone() const override;
    string build() const override;
};

class SanityPath : public SanityPartBuilder {
protected:
    vector<SanityPartBuilder*> m_parts;
public:
    SanityPath();
    void AddPart(string part);
    void AddArrayPart(string part);
    void AddProjectionPart(const SanityObjectProjection& projection);
    void Reset();
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_PATH_H
