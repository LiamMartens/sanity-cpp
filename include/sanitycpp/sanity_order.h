#ifndef SANITY_ORDER_H
#define SANITY_ORDER_H

#include <string>
#include <vector>

#include "sanity_modifier.h"

using namespace std;

struct SanityOrderPart {
    string name;
    bool asc;
};

class SanityOrder : public SanityModifier {
private:
    vector<SanityOrderPart> m_parts;
public:
    SanityOrder(string name = "", bool asc = true);
    void AddOrderPart(string name, bool asc = true);
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_ORDER_H