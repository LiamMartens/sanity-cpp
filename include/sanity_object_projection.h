#ifndef SANITY_OBJECT_PROJECTION_H
#define SANITY_OBJECT_PROJECTION_H

#include <string>
#include "sanity_query.h"
#include "sanity_path.h"

using namespace std;

class SanityPath;
class SanityObjectProjection;
class SanityQuery;
class SanityObjectProjection;

class SanityObjectProjectionProperty : public SanityPartBuilder {
private:
    /** @var rename for the property */
    string m_rename;
    /** @var path to connect to */
    SanityPath* m_path = nullptr;
    /** @var sub projection */
    SanityObjectProjection* m_subprojection = nullptr;
    /** @var sub query */
    SanityQuery* m_subquery = nullptr;

public:
    SanityObjectProjectionProperty();
    SanityObjectProjectionProperty(string name, string rename = "");

    SanityObjectProjectionProperty(const SanityObjectProjectionProperty& prop);
    SanityObjectProjectionProperty& operator=(const SanityObjectProjectionProperty& part) =default;
    ~SanityObjectProjectionProperty();

    void SetRename(string rename);
    void SetPath(const SanityPath& path);
    void SetSubprojection(const SanityObjectProjection& projection);
    void SetSubquery(const SanityQuery& query);

    string Rename() const;
    SanityPath* Path() const;
    SanityObjectProjection* Subprojection() const;
    SanityQuery* Subquery() const;
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
