#include "sanity_string.h"
#include "sanity_in_filter.h"

SanityInFilter::SanityInFilter() {
    this->m_type = SanityPartBuilderType::IN_FILTER;
}

SanityInFilter::SanityInFilter(string name) : SanityInFilter() {
    this->m_name = name;
}

/**
 * Adds a simple parameter to find in
 * @param string name The param to add
 */
void SanityInFilter::AddParam(string name) {
    this->m_in_params.push_back(name);
}

/**
 * Sets a path parameter to find in
 * @param string path The path parameter to find in
 */
void SanityInFilter::SetPathParam(string path) {
    this->m_path_param = path;
}

/**
 * Sets a raw parameter to find in
 * @param string raw
 */
void SanityInFilter::SetRawParam(string raw) {
    this->m_raw_param = raw;
}

/**
 * Creates a clone of the in filter
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityInFilter::clone() const {
    return new SanityInFilter(*this);
}

/**
 * Builds the 'in' filter
 * @return string const
 */
string SanityInFilter::build() const {
    string in_filter = "";
    if(this->m_in_params.size() > 0) {
        for(auto param : this->m_in_params) {
            if(in_filter.empty()) {
                in_filter = "[" + in_filter;
            } else {
                in_filter = in_filter + ",";
            }
            in_filter = in_filter + param;
        }
        in_filter = in_filter + "]";
    } else if(!this->m_path_param.empty()) {
        in_filter = "path(" + SanityString::QuoteWrap(this->m_path_param) + ")";
    } else if(!this->m_raw_param.empty()) {
        in_filter = this->m_raw_param;
    }

    char buff[this->m_name.size() + in_filter.size() + 2 + 2];
    sprintf(
        buff,
        "%s in %s",
        this->m_name.c_str(),
        in_filter.c_str()
    );

    return string(buff);
}
