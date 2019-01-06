#include "sanity_object_projection.h"
#include "sanity_string.h"

#pragma region SanityObjectProjectionProperty
SanityObjectProjectionProperty::SanityObjectProjectionProperty() {
    this->m_type = SanityPartBuilderType::OBJECT_PROJECTION_PROPERTY;
}

SanityObjectProjectionProperty::SanityObjectProjectionProperty(string name, string rename)
    : SanityObjectProjectionProperty() {
    this->m_path = new SanityPath();
    this->m_path->AddPart(name);
    this->m_rename = rename;
}

SanityObjectProjectionProperty::SanityObjectProjectionProperty(const SanityObjectProjectionProperty& prop)
    : SanityObjectProjectionProperty() {

    this->m_rename = prop.Rename();

    if(prop.Path() != nullptr) {
        SanityPath* p = new SanityPath(*prop.Path());
        this->m_path = p;
    }

    if(prop.Subprojection() != nullptr) {
        SanityObjectProjection* subproj = new SanityObjectProjection(*prop.Subprojection());
        this->m_subprojection = subproj;
    }
}

SanityObjectProjectionProperty::~SanityObjectProjectionProperty() {
    if(this->m_path != nullptr) {
        delete this->m_path;
    }

    if(this->m_subprojection != nullptr) {
        delete this->m_subprojection;
    }

    if(this->m_subquery != nullptr) {
        delete this->m_subquery;
    }
}

/**
 * Sets the rename variable
 * @param string rename
 */
void SanityObjectProjectionProperty::SetRename(string rename) {
    this->m_rename = rename;
}

/**
 * Sets the path to use
 * @param const SanityPath& path
 */
void SanityObjectProjectionProperty::SetPath(const SanityPath& path) {
    this->m_path = (SanityPath*)path.clone();
}

/**
 * Sets the object projection to use
 * @param const SanityObjcetProjection& projection
 */
void SanityObjectProjectionProperty::SetSubprojection(const SanityObjectProjection& projection) {
    this->m_subprojection = (SanityObjectProjection*)projection.clone();
}

/**
 * Sets the query to use
 * @param const SanityQuery* query
 */
void SanityObjectProjectionProperty::SetSubquery(const SanityQuery& query) {
    this->m_subquery = (SanityQuery*)query.clone();
}

/**
 * Returns the rename string
 * @return string const
 */
string SanityObjectProjectionProperty::Rename() const {
    return string(this->m_rename);
}

/**
 * Returns the property path
 * @reutrn SanityPath const
 */
SanityPath* SanityObjectProjectionProperty::Path() const {
    if(this->m_path != nullptr) {
        return new SanityPath(*this->m_path);
    }

    return nullptr;
}

/**
 * Gets the subprojection pointer
 * @return SanityObjectProjection* const
 */
SanityObjectProjection* SanityObjectProjectionProperty::Subprojection() const {
    if(this->m_subprojection != nullptr) {
        return (SanityObjectProjection*)this->m_subprojection->clone();
    }

    return nullptr;
}

/**
 * Gets the current subquery
 * @return SanityQuery* const
 */
SanityQuery* SanityObjectProjectionProperty::Subquery() const {
    if(this->m_subquery != nullptr) {
        return (SanityQuery*)this->m_subquery->clone();
    }

    return nullptr;
}

/**
 * Creates a clone of the object projection property
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityObjectProjectionProperty::clone() const {
    SanityObjectProjectionProperty* prop = new SanityObjectProjectionProperty;
    prop->SetRename(this->m_rename);
    if(this->m_path != nullptr) {
        SanityPath* path_copy = (SanityPath*)this->m_path->clone();
        prop->SetPath(*path_copy);
    }
    if(this->m_subprojection != nullptr) {
        SanityObjectProjection* proj_copy = (SanityObjectProjection*)this->m_subprojection->clone();
        prop->SetSubprojection(*proj_copy);
    }
    if(this->m_subquery != nullptr) {
        SanityQuery* query_copy = (SanityQuery*)this->m_subquery->clone();
        prop->SetSubquery(*query_copy);
    }
    return prop;
}

/**
 * Builds the projection property
 * @return string const
 */
string SanityObjectProjectionProperty::build() const {
    bool hasRename = !this->m_rename.empty();
    bool hasSubprojection = this->m_subprojection != nullptr;
    bool hasSubquery = this->m_subquery != nullptr;

    if (
        !hasRename
        && !hasSubprojection
    ) {
        return this->m_path->build();
    }

    if (
        !hasRename
        && hasSubprojection
    ) {
        return this->m_path->build() + this->m_subprojection->build();
    }

    string built_prop =
        SanityString::QuoteWrap(this->m_rename) +
        ":" +
        (hasSubquery ?
            this->m_subquery->build()
            : this->m_path->build());

    if (hasSubprojection) {
        built_prop = built_prop + this->m_subprojection->build();
    }

    return built_prop;
}
#pragma endregion

#pragma region SanityObjectProjection
SanityObjectProjection::SanityObjectProjection() {
    this->m_type = SanityPartBuilderType::OBJECT_PROJECTION;
}

SanityObjectProjection::SanityObjectProjection(const SanityObjectProjection& proj)
    : SanityObjectProjection() {
    for(auto prop : proj.m_props) {
        SanityObjectProjectionProperty* prop_copy = (SanityObjectProjectionProperty*)prop->clone();
        this->m_props.push_back(prop_copy);
    }
}

SanityObjectProjection::~SanityObjectProjection() {
    while(!this->m_props.empty()) {
        SanityObjectProjectionProperty* prop = this->m_props.back();
        delete prop;
        this->m_props.pop_back();
    }
}

/**
 * Adds a projection property object
 * @param const SanityObjectProjectionProperty& prop
 */
void SanityObjectProjection::AddProperty(const SanityObjectProjectionProperty& prop) {
    SanityObjectProjectionProperty* prop_ref = (SanityObjectProjectionProperty*)prop.clone();
    this->m_props.push_back(prop_ref);
}

/**
 * Creates a clone of the object projection
 * @return SanityPartBuilder* clone
 */
SanityPartBuilder* SanityObjectProjection::clone() const {
    SanityObjectProjection* proj = new SanityObjectProjection();
    for(auto prop : this->m_props) {
        SanityObjectProjectionProperty* prop_copy = (SanityObjectProjectionProperty*)prop->clone();
        proj->m_props.push_back(prop_copy);
    }
    return proj;
}

/**
 * Builds the complete projection
 * @return string const
 */
string SanityObjectProjection::build() const {
    string build = "";
    for(auto prop : this->m_props) {
        if(!build.empty()) {
            build = build + ",";
        } else {
            build = "{";
        }
        build = build + prop->build();
    }
    build = build + "}";
    return build;
}
#pragma endregion