#ifndef SANITY_PATCH_DIFFMATCH_MUTATION_H
#define SANITY_PATCH_DIFFMATCH_MUTATION_H

#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include "sanity_patch_mutation.h"

using json = nlohmann::json;
using namespace std;

class SanityPatchDiffMatchMutation : public SanityPatchMutation {
private:
    /** @var The diff match patch to apply (https://github.com/google/diff-match-patch) */
    map<string, string> m_dffms;
public:
    SanityPatchDiffMatchMutation();

    void AddDiffMatch(string key, string dffm);

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_PATCH_DIFFMATCH_MUTATION_H