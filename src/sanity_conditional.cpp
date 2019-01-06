#include "sanity_conditional.h"
#include "sanity_string.h"

#pragma region constructors
SanityConditional::SanityConditional() {
    this->m_type = SanityPartBuilderType::CONDITIONAL;
}

SanityConditional::SanityConditional(const SanityConditional& conditional) {
    if(conditional.m_filter != nullptr) {
        this->m_filter = (SanityFilter*)conditional.m_filter->clone();
    }
}

SanityConditional::~SanityConditional() {
    if(this->m_filter != nullptr) {
        delete this->m_filter;
    }

    if(this->m_builder != nullptr) {
        delete this->m_builder;
    }

    if(this->m_string_value != nullptr) {
        delete this->m_string_value;
    }

    if(this->m_long_value != nullptr) {
        delete this->m_long_value;
    }

    if(this->m_double_value != nullptr) {
        delete this->m_double_value;
    }

    if(this->m_bool_value != nullptr) {
        delete this->m_bool_value;
    }
}
#pragma endregion

#pragma region setters
/**
 * Sets the filter to use in the conditional
 * @param const SanityFilter& filter
 */
void SanityConditional::SetFilter(const SanityFilter& filter) {
    this->m_filter = (SanityFilter*)filter.clone();
}

/**
 * Sets the string value to use
 * @param string value
 */
void SanityConditional::SetStringValue(string value) {
    this->m_string_value = new string(value);
}

/**
 * Sets the simple long value
 * @param long value
 */
void SanityConditional::SetLongValue(long value) {
    this->m_long_value = new long(value);
}

/**
 * Sets the simple double value
 * @param double value
 */
void SanityConditional::SetDoubleValue(double value) {
    this->m_double_value = new double(value);
}

/**
 * Sets the simple bool value
 * @param bool value
 */
void SanityConditional::SetBoolValue(bool value) {
    this->m_bool_value = new bool(value);
}

/**
 * Sets the builder to use
 * @param const SanityPartBuilder& builder
 */
void SanityConditional::SetBuilder(const SanityPartBuilder& builder) {
    this->m_builder = builder.clone();
}
#pragma endregion

/**
 * Creates a clone of the conditional
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityConditional::clone() const {
    SanityConditional* copy = new SanityConditional();

    if(this->m_filter != nullptr) {
        copy->m_filter = (SanityFilter*)this->m_filter->clone();
    }

    if(this->m_string_value != nullptr) {
        copy->m_string_value = new string(*this->m_string_value);
    }
    copy->m_long_value = this->m_long_value;
    copy->m_double_value = this->m_double_value;
    copy->m_bool_value = this->m_bool_value;

    if(this->m_builder != nullptr) {
        copy->m_builder = this->m_builder->clone();
    }

    return copy;
}

/**
 * Builds the conditional
 * @return string const
 */
string SanityConditional::build() const {
    string build = "";

    if(this->m_filter == nullptr) {
        throw NoFilterException();
    }

    bool hasStringValue = this->m_string_value != nullptr;
    bool hasLongValue = this->m_long_value != nullptr;
    bool hasDoubleValue = this->m_double_value != nullptr;
    bool hasBoolValue = this->m_bool_value != nullptr;
    bool hasBuilder = this->m_builder != nullptr;

    if(
        !hasStringValue
        && !hasLongValue
        && !hasDoubleValue
        && !hasBoolValue
        && !hasBuilder
    ) {
        throw NoValueException();
    }

    build = build + this->m_filter->build() + " => ";

    if(hasStringValue) {
        build = build + SanityString::QuoteWrap(*this->m_string_value);
    } else if(hasLongValue) {
        build = build + to_string(*this->m_long_value);
    } else if(hasDoubleValue) {
        build = build + to_string(*this->m_double_value);
    } else if(hasBoolValue) {
        build = build + (*this->m_bool_value ? "true" : "false");
    } else if(hasBuilder) {
        build = build + this->m_builder->build();
    }

    return build;
}
