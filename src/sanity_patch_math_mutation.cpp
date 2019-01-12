#include "sanity_patch_math_mutation.h"

#pragma region constructors
SanityPatchMathMutation::SanityPatchMathMutation() {
    this->m_type = SanityPartBuilderType::PATCH_MATH;
}

SanityPatchMathMutation::SanityPatchMathMutation(string key, double value) {
    this->AddItem(key, value);
}

SanityPatchMathMutation::SanityPatchMathMutation(string key, long value) {
    this->AddItem(key, value);
}
#pragma endregion

/**
 * Returns the name of the operation
 * @return string const
 */
string SanityPatchMathMutation::OperationName() const {
    switch(this->m_operation) {
        case SanityPatchMathOperation::INC:
            return "inc";
        case SanityPatchMathOperation::DEC:
            return "dec";
    }

    throw InvalidOperationException();
}

/**
 * Sets the operation to inc
 */
void SanityPatchMathMutation::Inc() {
    this->m_operation = SanityPatchMathOperation::INC;
}

/**
 * Sets the operation to dec
 */
void SanityPatchMathMutation::Dec() {
    this->m_operation = SanityPatchMathOperation::DEC;
}

/**
 * Adds an operation item
 * @param string key
 * @param double value
 */
void SanityPatchMathMutation::AddItem(string key, double value) {
    SanityPatchMathMutationItem item(value);
    this->m_items.insert(pair<string, SanityPatchMathMutationItem>(key, item));
}

/**
 * Adds an operation item
 * @param string key
 * @param long value
 */
void SanityPatchMathMutation::AddItem(string key, long value) {
    SanityPatchMathMutationItem item(value);
    this->m_items.insert(pair<string, SanityPatchMathMutationItem>(key, item));
}

/**
 * Creates a clone of the math operation
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityPatchMathMutation::clone() const {
    SanityPatchMathMutation* mut = new SanityPatchMathMutation();
    mut->m_operation = this->m_operation;
    for(auto op : this->m_items) {
        SanityPatchMathMutationItem value = op.second;
        switch(value.Type) {
            case SanityPatchMathMutationItemType::LONG:
                mut->AddItem(op.first, value.LongValue);
                break;
            case SanityPatchMathMutationItemType::DOUBLE:
                mut->AddItem(op.first, value.DoubleValue);
                break;
        }
    }
    return mut;
}

/**
 * Builds the math operatiom
 * @return string const
 */
string SanityPatchMathMutation::build() const {
    json ops;
    for(auto op : this->m_items) {
        SanityPatchMathMutationItem value = op.second;
        switch(value.Type) {
            case SanityPatchMathMutationItemType::LONG:
                ops[op.first] = value.LongValue;
                break;
            case SanityPatchMathMutationItemType::DOUBLE:
                ops[op.first] = value.DoubleValue;
                break;
        }
    }

    json mut = {
        {this->OperationName(), ops}
    };

    return mut.dump();
}
