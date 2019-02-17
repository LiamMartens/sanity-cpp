#ifndef SANITY_STRING_H
#define SANITY_STRING_H

#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <iostream>
#include "sanity_part_builder.h"

using namespace std;

class SanityString {
public:
    static string QuoteWrap(string s);
    static vector<string> Split(string s, char c);
    static string Join(vector<SanityPartBuilder*> items, string delim = ",");
    static string Join(vector<SanityPartBuilder> items, string delim = ",");
    static string Join(vector<string> items, string delim = ",");
    static string PadStartToLength(string from, unsigned int len, char c);
    static string PadEndToLength(string from, unsigned int len, char c);
    static string ToHex(long nr, unsigned int min_len = 0);
    static string Trim(string inp, char c = ' ');
};

#endif // SANITY_STRING_H