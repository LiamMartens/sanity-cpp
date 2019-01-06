#include "sanity_select.h"
#include "sanity_string.h"

#pragma region constructors
SanitySelect::SanitySelect() {
    this->m_type = SanityPartBuilderType::SELECT;
}

SanitySelect::~SanitySelect() {
    while(!this->m_options.empty()) {
        SanityPartBuilder* opt = this->m_options.back();
        delete opt;
        this->m_options.pop_back();
    }
}
#pragma endregion

/**
 * Adds an option to the select
 * @param const SanityPartBuilder& builder
 */
void SanitySelect::AddOption(const SanityPartBuilder& builder) {
    SanityPartBuilder* cloned = builder.clone();
    this->m_options.push_back(cloned);
}

/**
 * Creates a clone of the select statement
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanitySelect::clone() const {
    SanitySelect* cloned = new SanitySelect();
    for(auto opt : this->m_options) {
        cloned->AddOption(*opt);
    }
    return cloned;
}

/**
 * Builds the select statement
 * @return string const
 */
string SanitySelect::build() const {
    string build = SanityString::Join(this->m_options);
    return "select(" + build + ")";
}

