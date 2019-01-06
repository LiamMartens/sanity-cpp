#ifndef SANITY_SELECT_H
#define SANITY_SELECT_H

#include <string>
#include <vector>
#include "sanity_part_builder.h"

using namespace std;

class SanitySelect : public SanityPartBuilder {
private:
    vector<SanityPartBuilder*> m_options;
public:
    #pragma region constructors
    SanitySelect();
    ~SanitySelect();
    #pragma endregion

    void AddOption(const SanityPartBuilder& builder);

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_SELECT_H