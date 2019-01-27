#include "sanity_string.h"

/**
 * Wraps the string in double quotes
 * for use in queries and printing
 * @return string
 */
string SanityString::QuoteWrap(string s) {
    return '"' + s + '"';
}

/**
 * Splits a string on a character
 * @param string s
 * @param char c
 * @return vector<string>
 */
vector<string> SanityString::Split(string s, char c) {
    vector<string> parts;
    string leftover = s;
    size_t next_idx = s.find(c);
    while(next_idx != string::npos) {
        string part = leftover.substr(0, next_idx);
        parts.push_back(part);
        leftover = leftover.substr(next_idx + 1);
        next_idx = leftover.find(c);
    }
    if(!leftover.empty()) {
        parts.push_back(leftover);
    }
    return parts;
}

/**
 * Joins the vector items together
 * @param vector<SanityPartBuilder*
 */
string SanityString::Join(vector<SanityPartBuilder*> items, string delim) {
    string joined = "";
    for(auto item : items) {
        if(!joined.empty()) {
            joined = joined + delim;
        }
        joined  = joined + item->build();
    }
    return joined;
}

/**
 * Joins the vector items together
 * @param vector<SanityPartBuilder*
 */
string SanityString::Join(vector<SanityPartBuilder> items, string delim) {
    string joined = "";
    for(auto item : items) {
        if(!joined.empty()) {
            joined = joined + delim;
        }
        joined = joined + item.build();
    }
    return joined;
}

/**
 * Joins the vector items together
 * @param vector<string>
 */
string SanityString::Join(vector<string> items, string delim) {
    string joined = "";
    for(auto item : items) {
        if(!joined.empty()) {
            joined = joined + delim;
        }
        joined = joined + item;
    }
    return joined;
}

/**
 * @brief Pads a string to a certain length with a character
 *
 * @param from
 * @param len
 * @param c
 * @return string
 */
string SanityString::PadStartToLength(string from, unsigned int len, char c) {
    string n = string(from);
    n.insert(n.begin(), len - n.length(), c);
    return n;
}

/**
 * @brief Pads a sring to a certain length with a character
 *
 * @param from
 * @param len
 * @param c
 * @return string
 */
string SanityString::PadEndToLength(string from, unsigned int len, char c) {
    string n = from;
    n.append(len - n.length(), c);
    return n;
}
