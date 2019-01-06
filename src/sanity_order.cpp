#include "sanity_order.h"

SanityOrder::SanityOrder(string name, bool asc) {
    this->m_type = SanityPartBuilderType::ORDER;

    if(!name.empty()) {
        SanityOrderPart p = { name, asc };
        this->m_parts.push_back(p);
    }
}

/**
 * Adds an additional order part
 * @param string name Name of the order column
 * @param bool asc Sorting direction
 */
void SanityOrder::AddOrderPart(string name, bool asc) {
    SanityOrderPart p { name, asc };
    this->m_parts.push_back(p);
}

/**
 * Creates a clone of the order object
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityOrder::clone() const {
    return new SanityOrder(*this);
}

/**
 * Builds the order string
 * @return string const
 */
string SanityOrder::build() const {
    string built = "";
    for(auto part : this->m_parts) {
        if(!built.empty()) {
            built = built + ",";
        }
        built = built + part.name + " " + (part.asc ? "asc" : "desc");
    }
    return "order(" + built + ")";
}
