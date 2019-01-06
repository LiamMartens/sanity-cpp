#ifndef SANITY_OBJECT_PROJECTION_H
#define SANITY_OBJECT_PROJECTION_H

#include <string>
#include "sanity_query.h"
#include "sanity_path.h"
#include "sanity_part_builder.h"

using namespace std;

class SanityPath;
class SanityObjectProjection;
class SanityQuery;
class SanityObjectProjection;

class SanityObjectProjectionProperty : public SanityPartBuilder {
private:
    /** @var rename for the property */
    string m_rename;
    /** @var value to use */
    SanityPartBuilder* m_value = nullptr;
    /** @var sub projection */
    SanityObjectProjection* m_subprojection = nullptr;

public:
    SanityObjectProjectionProperty();
    SanityObjectProjectionProperty(string name, string rename = "");

    SanityObjectProjectionProperty(const SanityObjectProjectionProperty& prop);
    SanityObjectProjectionProperty& operator=(const SanityObjectProjectionProperty& part) =default;
    ~SanityObjectProjectionProperty();

    void SetRename(string rename);
    void SetValue(const SanityPartBuilder& value);
    void SetSubprojection(const SanityObjectProjection& projection);

    string Rename() const;
    SanityPartBuilder* Value() const;
    SanityObjectProjection* Subprojection() const;
    SanityPartBuilder* clone() const override;
    string build() const override;
};

class SanityObjectProjection : public SanityPartBuilder {
private:
    vector<SanityObjectProjectionProperty*> m_props;
public:
    SanityObjectProjection();
    SanityObjectProjection(const SanityObjectProjection& proj);
    ~SanityObjectProjection();
    void AddProperty(const SanityObjectProjectionProperty& prop);
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_OBJECT_PROJECTION_H
