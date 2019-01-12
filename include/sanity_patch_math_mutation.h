#ifndef SANITY_PATCH_MATH_MUTATION_H
#define SANITY_PATCH_MATH_MUTATION_H

#include <string>
#include <map>
#include <math.h>
#include <nlohmann/json.hpp>
#include "sanity_patch_mutation.h"

using json = nlohmann::json;
using namespace std;

enum class SanityPatchMathMutationItemType {
    LONG,
    DOUBLE
};

class SanityPatchMathMutationItem {
public:
    SanityPatchMathMutationItemType Type;
    long LongValue;
    double DoubleValue;

    SanityPatchMathMutationItem(long value) {
        this->Type = SanityPatchMathMutationItemType::LONG;
        this->LongValue = value;
    };

    SanityPatchMathMutationItem(double value) {
        this->Type = SanityPatchMathMutationItemType::DOUBLE;
        this->DoubleValue = value;
    };

};

enum class SanityPatchMathOperation {
    INC,
    DEC
};

class InvalidOperationException
    : public exception {
    const char* what() const throw() {
        return "Invalid operation";
    }
};

class SanityPatchMathMutation : public SanityPatchMutation {
private:
    SanityPatchMathOperation m_operation = SanityPatchMathOperation::INC;
    /** @var items to increase/decrease */
    map<string, SanityPatchMathMutationItem> m_items;
public:
    #pragma region constructors
    SanityPatchMathMutation();
    SanityPatchMathMutation(string key, double value);
    SanityPatchMathMutation(string key, long value);
    #pragma endregion

    string OperationName() const;

    void Inc();
    void Dec();
    void AddItem(string key, double value);
    void AddItem(string key, long value);

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_PATCH_MATH_MUTATION_H