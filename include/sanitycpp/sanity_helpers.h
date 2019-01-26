#ifndef SANITY_HELPERS_H
#define SANITY_HELPERS_H

#include <map>
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
};

#endif // SANITY_HELPERS_H