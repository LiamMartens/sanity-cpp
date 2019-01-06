#include "sanity_object_projection.h"
#include "sanity_string.h"

#pragma region SanityObjectProjectionProperty
SanityObjectProjectionProperty::SanityObjectProjectionProperty() {
    this->m_type = SanityPartBuilderType::OBJECT_PROJECTION_PROPERTY;
}

SanityObjectProjectionProperty::SanityObjectProjectionProperty(string name, string rename)
    : SanityObjectProjectionProperty() {
    SanityPath* p = new SanityPath();
    p->AddPart(name);
    this->m_value = p;
    this->m_rename = rename;
}

SanityObjectProjectionProperty::SanityObjectProjectionProperty(const SanityObjectProjectionProperty& prop)
    : SanityObjectProjectionProperty() {

    this->m_rename = prop.Rename();

    if(prop.m_value != nullptr) {
        SanityPartBuilder* p = prop.m_value->clone();
        this->m_value = p;
    }

    if(prop.Subprojection() != nullptr) {
        SanityObjectProjection* subproj = (SanityObjectProjection*)prop.m_subprojection->clone();
        this->m_subprojection = subproj;
    }
}

SanityObjectProjectionProperty::~SanityObjectProjectionProperty() {
    if(this->m_value != nullptr) {
        delete this->m_value;
    }

    if(this->m_subprojection != nullptr) {
        delete this->m_subprojection;
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
 * Sets the query to use
 * @param const SanityQuery* query
 */
void SanityObjectProjectionProperty::SetValue(const SanityPartBuilder& query) {
    this->m_value = query.clone();
}

/**
 * Sets the object projection to use
 * @param const SanityObjcetProjection& projection
 */
void SanityObjectProjectionProperty::SetSubprojection(const SanityObjectProjection& projection) {
    this->m_subprojection = (SanityObjectProjection*)projection.clone();
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
SanityPartBuilder* SanityObjectProjectionProperty::Value() const {
    if(this->m_value != nullptr) {
        return this->m_value->clone();
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
 * Creates a clone of the object projection property
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityObjectProjectionProperty::clone() const {
    SanityObjectProjectionProperty* prop = new SanityObjectProjectionProperty;
    prop->SetRename(this->m_rename);
    if(this->m_value != nullptr) {
        SanityPartBuilder* value_copy = (SanityPartBuilder*)this->m_value->clone();
        prop->SetValue(*value_copy);
    }
    if(this->m_subprojection != nullptr) {
        SanityObjectProjection* proj_copy = (SanityObjectProjection*)this->m_subprojection->clone();
        prop->SetSubprojection(*proj_copy);
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
    bool hasValue = this->m_value != nullptr;

    if (
        !hasRename
        && !hasSubprojection
    ) {
        return this->m_value->build();
    }

    if (
        !hasRename
        && hasSubprojection
    ) {
        return this->m_value->build() + this->m_subprojection->build();
    }

    string built_prop =
        SanityString::QuoteWrap(this->m_rename) +
        ":" +
        this->m_value->build();

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