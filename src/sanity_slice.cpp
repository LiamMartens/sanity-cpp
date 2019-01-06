#include "sanity_slice.h"

SanitySlice::SanitySlice() {
    this->m_type = SanityPartBuilderType::SLICE;
}

SanitySlice::SanitySlice(int from, int to) : SanitySlice() {
    this->m_from = from;
    this->m_to = to;
}

/**
 * Creates a copy of the slice object
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanitySlice::clone() const {
    return new SanitySlice(*this);
}

/**
 * Creates the built slice string
 * @return string const
 */
string SanitySlice::build() const {
    if(this->m_to == -1) {
        return "[" + to_string(this->m_from) + "]";
    }

    return "[" + to_string(this->m_from) + "..." + to_string(this->m_to) + "]";
}