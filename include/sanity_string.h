#ifndef SANITY_STRING_H
#define SANITY_STRING_H

#include <string>
#include <vector>
#include "sanity_part_builder.h"

using namespace std;

class SanityString {
public:
    static string QuoteWrap(string s);
    static string Join(vector<SanityPartBuilder*> items);
    static string Join(vector<SanityPartBuilder> items);
};

#endif // SANITY_STRING_H