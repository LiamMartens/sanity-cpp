#ifndef SANITY_CONDITIONAL_H
#define SANITY_CONDITIONAL_H

#include <string>
#include "sanity_filter.h"
#include "sanity_part_builder.h"

using namespace std;

struct NoFilterException
    : public exception {
    const char* what() const throw() {
        return "No filter set";
    }
};

struct NoValueException
    : public exception {
    const char* what() const throw() {
        return "No value set";
    }
};

class SanityConditional : public SanityPartBuilder {
private:
    /** @var The filter to use in the conditional */
    SanityFilter* m_filter = nullptr;

    /** @var Simple value types */
    string* m_string_value = nullptr;
    long* m_long_value = nullptr;
    double* m_double_value = nullptr;
    bool* m_bool_value = nullptr;
    /** @var any other part builder */
    SanityPartBuilder* m_builder = nullptr;

public:
    #pragma region constructors
    SanityConditional();
    SanityConditional(const SanityConditional& conditional);
    ~SanityConditional();
    #pragma endregion

    #pragma region setters
    void SetFilter(const SanityFilter& filter);
    void SetStringValue(string value);
    void SetLongValue(long value);
    void SetDoubleValue(double value);
    void SetBoolValue(bool value);
    void SetBuilder(const SanityPartBuilder& builder);
    #pragma endregion

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_CONDITIONAL_H