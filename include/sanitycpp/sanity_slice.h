#ifndef SANITY_SLICE_H
#define SANITY_SLICE_H

#include <string>
#include "sanity_part_builder.h"

using namespace std;

class SanitySlice : public SanityPartBuilder {
private:
    int m_from = 0;
    int m_to = -1;

    SanitySlice();
public:
    SanitySlice(int from, int to = -1);
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_SLICE_H