#include "sanity_filter.h"

#pragma region SanityFilterPart
SanityFilterPart::SanityFilterPart() {
    this->m_type = SanityPartBuilderType::FILTER_PART;
}

SanityFilterPart::SanityFilterPart(const SanityFilterPart& part)
    : SanityFilterPart() {
    this->m_op = part.m_op;
    this->m_builder = part.m_builder->clone();
}

SanityFilterPart::SanityFilterPart(const SanityPartBuilder& builder)
    :SanityFilterPart() {
    this->m_builder = builder.clone();
}

SanityFilterPart::SanityFilterPart(const SanityPartBuilder& builder, SanityFilterOperator op)
    : SanityFilterPart(builder) {
    this->m_op = op;
}

SanityFilterPart::~SanityFilterPart() {
    if(this->m_builder != nullptr) {
        delete this->m_builder;
    }
}

/**
 * Creates a clone of the filter part
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityFilterPart::clone() const {
    return new SanityFilterPart(*this);
}

/**
 * Builds the filter part
 * @return string const
 */
string SanityFilterPart::build() const {
    string built = this->m_builder->build();

    if(this->m_op == SanityFilterOperator::NONE) {
        return built;
    }

    string op = "";
    switch(this->m_op) {
        case SanityFilterOperator::AND:
            op = "&&";
            break;
        case SanityFilterOperator::OR:
            op = "||";
            break;
    }

    return op + " " + built;
}
#pragma endregion

SanityFilter::SanityFilter() {
    this->m_type = SanityPartBuilderType::FILTER;
}

SanityFilter::SanityFilter(const SanityFilter& filter)
    : SanityFilter() {
    for(auto part : filter.m_parts) {
        SanityFilterPart* p = new SanityFilterPart(*part);
        this->m_parts.push_back(p);
    }
}

SanityFilter::~SanityFilter() {
    while(!this->m_parts.empty()) {
        SanityFilterPart* part = this->m_parts.back();
        delete part;
        this->m_parts.pop_back();
    }
}

/**
 * Add a part to the filter
 * @param const SanityPartBuilder& builder The builder to add
 * @param SanityFilterOperator op The operator to us
 */
void SanityFilter::AddPart(const SanityPartBuilder& builder, SanityFilterOperator op) {
    SanityFilterPart* part = new SanityFilterPart(builder, op);
    this->m_parts.push_back(part);
}

/**
 * Creats a clone of the filter object
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityFilter::clone() const {
    return new SanityFilter(*this);
}

/**
 * Builds the filter
 * @return string
 */
string SanityFilter::build() const {
    string built = "";
    for(auto part : this->m_parts) {
        if(!built.empty()) {
            built = built + " ";
        }
        built = built + part->build();
    }

    return built;
}

