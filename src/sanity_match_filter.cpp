#include "sanity_match_filter.h"

SanityMatchFilter::SanityMatchFilter(string param, string match) {
    this->m_type = SanityPartBuilderType::MATCH_FILTER;
    this->m_param = param;
    this->m_match = match;
}

/**
 * Sets the param to match aginst
 * @param string param The param to match against
 */
void SanityMatchFilter::SetParam(string param) {
    this->m_param = param;
}

/**
 * Adds a param to match for
 * @param string parm The param to match for
 */
void SanityMatchFilter::AddParam(string param) {
    this->m_params.push_back(param);
}

/**
 * Sets the single match param
 * @param string match The param to match against
 */
void SanityMatchFilter::SetMatch(string match) {
    this->m_match = match;
}

/**
 * Adds a match parameter
 * @param string match The param to match against
 */
void SanityMatchFilter::AddMatch(string match) {
    this->m_matches.push_back(match);
}

/**
 * Creates a clone of the match filter
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityMatchFilter::clone() const {
    return new SanityMatchFilter(*this);
}

/**
 * Builds the match filter
 * @return string const
 */
string SanityMatchFilter::build() const {
    string built_param = "";
    if(!this->m_param.empty()) {
        built_param = this->m_param;
    } else if(this->m_params.size() != 0) {
        for(auto param : this->m_params) {
            if(built_param.empty()) {
                built_param = "[" + built_param;
            } else {
                built_param = built_param + ",";
            }
            built_param = built_param + param;
        }
        built_param = built_param + "]";
    }

    string built_matches = "";
    if(!this->m_match.empty()) {
        built_matches = this->m_match;
    } else if(this->m_matches.size() != 0) {
        for(auto match : this->m_matches) {
            if(built_matches.empty()) {
                built_matches = "[" + built_matches;
            } else {
                built_matches = built_matches + ",";
            }
            built_matches = built_matches + match;
        }
        built_matches = built_matches + "]";
    }

    char buff[built_param.size() + built_matches.size() + 8];
    sprintf(
        buff,
        "%s match %s",
        built_param.c_str(),
        built_matches.c_str()
    );

    return string(buff);
}

