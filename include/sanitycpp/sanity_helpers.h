#ifndef SANITY_HELPERS_H
#define SANITY_HELPERS_H

#include <map>
#include "sanity_string.h"
using namespace std;

class SanityHelpers_OneOf_NoneFound
    : public exception {
    const char* what() const throw() {
        return "No match found";
    }
};

class SanityHelpers {
public:
    template<typename T>
    static T OneOf(const map<T, bool>& one_of_map) {
        for(auto item : one_of_map) {
            if(item.second) {
                return item.first;
            }
        }

        throw SanityHelpers_OneOf_NoneFound();
    };

    template<typename T>
    static T OneOf(const map<T, bool>& one_of_map, T def) {
        for(auto item : one_of_map) {
            if(item.second) {
                return item.first;
            }
        }

        return def;
    };

    static string TmToString(tm t, bool include_time = false) {
        string year = to_string(t.tm_year + 1900);
        string mon = SanityString::PadStartToLength(to_string(t.tm_mon + 1), 2, '0');
        string day = SanityString::PadStartToLength(to_string(t.tm_mday), 2, '0');

        if(include_time) {
            string hours = SanityString::PadStartToLength(to_string(t.tm_hour), 2, '0');
            string mins = SanityString::PadStartToLength(to_string(t.tm_min), 2, '0');
            string secs = SanityString::PadStartToLength(to_string(t.tm_sec), 2, '0');

            return
                year + "-" + mon + "-" + day
                + "T" + hours + ":" + mins + ":" + secs + "Z";
        }

        return year + "-" + mon + "-" + day;
    };
};

#endif // SANITY_HELPERS_H