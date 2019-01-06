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
 * Joins the vector items together
 * @param vector<SanityPartBuilder*
 */
string SanityString::Join(vector<SanityPartBuilder*> items) {
    string joined = "";
    for(auto item : items) {
        if(!joined.empty()) {
            joined = joined + ",";
        }
        joined  = joined + item->build();
    }
    return joined;
}

/**
 * Joins the vector items together
 * @param vector<SanityPartBuilder*
 */
string SanityString::Join(vector<SanityPartBuilder> items) {
    string joined = "";
    for(auto item : items) {
        if(!joined.empty()) {
            joined = joined + ",";
        }
        joined = joined + item.build();
    }
    return joined;
}