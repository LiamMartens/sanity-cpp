#ifndef SANITY_HELPERS_H
#define SANITY_HELPERS_H

#include <map>
#include <iostream>
#include <sstream>
#include <random>
#include <climits>
#include <functional>
#include <algorithm>
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
    /**
     * @brief Find one of by condition
     * 
     * @tparam T 
     * @param one_of_map 
     * @return T 
     */
    template<typename T>
    static T OneOf(const map<T, bool>& one_of_map) {
        for(auto item : one_of_map) {
            if(item.second) {
                return item.first;
            }
        }

        throw SanityHelpers_OneOf_NoneFound();
    };

    /**
     * @brief Find one of by condition and use default
     * 
     * @tparam T 
     * @param one_of_map 
     * @return T 
     */
    template<typename T>
    static T OneOf(const map<T, bool>& one_of_map, T def) {
        for(auto item : one_of_map) {
            if(item.second) {
                return item.first;
            }
        }

        return def;
    };

    /**
     * @brief Converts a tm object to string
     * 
     * @param t 
     * @param include_time 
     * @return string 
     */
    static string TmToString(tm t, bool include_time = true) {
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

    /**
     * @brief Converts a string to tm object
     * 
     * @param s 
     * @param include_time 
     * @return tm 
     */
    static tm TmFromString(string str, bool include_time = true) {
        int y,M,d,h,m;
        float s;

        if(include_time) {
            sscanf(str.c_str(), "%d-%d-%dT%d:%d:%fZ", &y, &M, &d, &h, &m, &s);
        } else {
            sscanf(str.c_str(), "%d-%d-%d", &y, &M, &d);
        }

        if(include_time) {
            return tm{
                .tm_sec = (int)s,
                .tm_min = m,
                .tm_hour = h,
                .tm_mday = d,
                .tm_mon = M - 1,
                .tm_year = y - 1900
            };
        }

        return tm{
            .tm_sec = 0,
            .tm_min = 0,
            .tm_hour = 0,
            .tm_mday = d,
            .tm_mon = M - 1,
            .tm_year = y - 1900
        };
    }

    /**
     * @brief Checks whether the tm is valid
     *
     * @param t
     * @return true
     * @return false
     */
    static bool IsValidTm(tm t) {
        if(
            t.tm_year < -1900
            || t.tm_mon < 0
            || t.tm_mon > 11
            || t.tm_mday < 1
            || t.tm_mday > 31
            || t.tm_hour < 0
            || t.tm_hour > 23
            || t.tm_min < 0
            || t.tm_min > 59
            || t.tm_sec < 0
            || t.tm_sec > 60
        ) {
            return false;
        }

        return true;
    };

    static unsigned char randomChar() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 255);
        return static_cast<unsigned char>(dis(gen));
    }

    static string generateKey(unsigned int len = 12) {
        stringstream ss;
        for(auto i = 0; i < len; i++) {
            unsigned char rc = SanityHelpers::randomChar();
            stringstream hexstream;
            hexstream << hex << int(rc);
            string hex = hexstream.str();
            ss << (hex.length() < 2 ? '0' + hex : hex);
        }
        return ss.str();
    }
};

#endif // SANITY_HELPERS_H