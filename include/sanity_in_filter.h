#ifndef SANITY_IN_FILTER_H
#define SANITY_IN_FILTER_H

#include <string>
#include <vector>
#include "sanity_part_builder.h"

using namespace std;

class SanityInFilter : public SanityPartBuilder {
private:
    /** @var name of the parameter */
    string m_name = "";
    /** @var parameters to find in */
    vector<string> m_in_params;
    /** @var path param */
    string m_path_param;
    /** @var raw param */
    string m_raw_param;

    SanityInFilter();
public:
    SanityInFilter(string name);
    void AddParam(string param);
    void SetPathParam(string path);
    void SetRawParam(string raw);
    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_IN_FILTER_H