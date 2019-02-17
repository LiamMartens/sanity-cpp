#ifndef SANITY_COLOR_H
#define SANITY_COLOR_H

#include <iomanip>
#include <regex>
#include <string>
#include <cmath>
#include <sstream>
#include "sanity_string.h"

using namespace std;

#pragma region exceptions
class SanityColor_InvalidColorParamException
    : public exception {
    const char* what() const throw() {
        return "Invalid color parameter (must be between 0 and 255)";
    }
};
#pragma endregion

class SanityColor {
private:
    /** @var Red */
    unsigned int m_r = 0;
    /** @var Green */
    unsigned int m_g = 0;
    /** @var Blue */
    unsigned int m_b = 0;
    /** @var Alpha */
    float m_a = 1;

public:
    SanityColor();
    SanityColor(string color);
    SanityColor(const char color[]);
    SanityColor(unsigned int r, unsigned int g, unsigned int b, float a = 1.0f);
    SanityColor(const SanityColor& color);

    #pragma region getters
    unsigned int R() const;
    unsigned int G() const;
    unsigned int B() const;
    float A() const;
    string Hex(bool include_alpha = false) const;
    string Rgb() const;
    string Rgba() const;
    #pragma endregion

    #pragma region setters
    void SetR(unsigned int r);
    void SetG(unsigned int g);
    void SetB(unsigned int b);
    void SetA(float a);
    #pragma endregion
};

#endif // SANITY_COLOR_H