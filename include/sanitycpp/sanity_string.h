#ifndef SANITY_STRING_H
#define SANITY_STRING_H

#include <string>
#include <vector>
#include "sanity_part_builder.h"

using namespace std;

class SanityString {
public:
    static string QuoteWrap(string s);
    static vector<string> Split(string s, char c);
    static string Join(vector<SanityPartBuilder*> items, string delim = ",");
    static string Join(vector<SanityPartBuilder> items, string delim = ",");
    static string Join(vector<string> items, string delim = ",");
};

#endif // SANITY_STRING_H