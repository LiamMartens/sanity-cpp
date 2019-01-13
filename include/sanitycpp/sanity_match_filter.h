#ifndef SANITY_MATCH_FILTER_H
#define SANITY_MATCH_FILTER_H

#include <string>
#include <vector>
#include "sanity_part_builder.h"

using namespace std;

class SanityMatchFilter : public SanityPartBuilder {
private:
    /** @var param to check */
    string m_param = "";
    /** @var params */
    vector<string> m_params;
    /** @var what to match against */
    string m_match = "";
    /** @var matches to match */
    vector<string> m_matches;
public:
    SanityMatchFilter(string param = "", string match = "");
    void SetParam(string param);
    void AddParam(string param);
    void SetMatch(string match);
    void AddMatch(string match);
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_MATCH_FILTER+H