#include "sanity_color.h"

SanityColor::SanityColor() {}

SanityColor::SanityColor(string color) {
    regex rx_rgb("^#[a-fA-F0-9]{3}$|^#[a-fA-F0-9]{6}$|^#[a-fA-F0-9]{8}$");
    regex rx_rgb2("^rgba?\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*(,\\s*((0|1)(\\.\\d+)?)\\s*)?\\)$");
    if(regex_match(color, rx_rgb)) {
        string clr = color.substr(1);
        if(clr.size() == 3) {
            clr = clr + clr;
        }

        this->SetR(strtol(clr.substr(0, 2).c_str(), 0, 16));
        this->SetG(strtol(clr.substr(2, 2).c_str(), 0, 16));
        this->SetB(strtol(clr.substr(4, 2).c_str(), 0, 16));
        if(clr.size() == 8) {
            this->SetA(strtol(clr.substr(6, 2).c_str(), 0, 16));
        }
    } else if(regex_match(color, rx_rgb2)) {
        string clr = color.substr(5, color.size() - 6);
        size_t deli_r_g = clr.find_first_of(',');
        size_t deli_g_b = clr.find_first_of(',', deli_r_g + 1);
        size_t deli_b_a = clr.find_first_of(',', deli_g_b + 1);
        this->SetR(stoi(clr.substr(0, deli_r_g)));
        this->SetG(stoi(clr.substr(deli_r_g + 1, deli_g_b - deli_r_g - 1)));
        if(deli_b_a == string::npos) {
            this->SetB(stoi(clr.substr(deli_g_b + 1)));
        } else {
            this->SetB(stoi(clr.substr(deli_g_b + 1, deli_b_a - deli_g_b - 1)));
            this->SetA(stof(clr.substr(deli_b_a + 1)));
        }
    }
}

SanityColor::SanityColor(const char color[])
    : SanityColor(string(color)) {
}

SanityColor::SanityColor(unsigned int r, unsigned int g, unsigned int b, float a) {
    this->SetR(r);
    this->SetG(g);
    this->SetB(b);
    this->SetA(a);
}

SanityColor::SanityColor(const SanityColor& color)
    : SanityColor(color.R(), color.G(), color.B(), color.A()) {
}

#pragma region getters
/**
 * @brief Gets the red value
 * 
 * @return unsigned int
 */
unsigned int SanityColor::R() const {
    return this->m_r;
}

/**
 * @brief Gets the green value
 *
 * @return unsigned int
 */
unsigned int SanityColor::G() const {
    return this->m_g;
}

/**
 * @brief Gets the blue value
 *
 * @return unsigned int
 */
unsigned int SanityColor::B() const {
    return this->m_b;
}

/**
 * @brief Gets the alpha value
 *
 * @return unsigned int
 */
float SanityColor::A() const {
    return this->m_a;
}

/**
 * @brief Converts the color to hex
 *
 * @return string
 */
string SanityColor::Hex(bool include_alpha) const {
    return "#"
        + SanityString::ToHex(this->R(), 2)
        + SanityString::ToHex(this->G(), 2)
        + SanityString::ToHex(this->B(), 2)
        + (include_alpha ? SanityString::ToHex(round(this->A() * 255.0f), 2) : "");
}

/**
 * @brief Converts the color to rgb
 *
 * @return string
 */
string SanityColor::Rgb() const {
    return "rgb("
        + to_string(this->R()) + ","
        + to_string(this->G()) + ","
        + to_string(this->B())
        + ")";
}

/**
 * @brief Converts the color to rgba
 *
 * @return string
 */
string SanityColor::Rgba() const {
    return "rgba("
        + to_string(this->R()) + ","
        + to_string(this->G()) + ","
        + to_string(this->B()) + ","
        + SanityString::Trim(regex_replace(to_string(this->A()), regex("(?!^)0*$"), ""), '.')
        + ")";
}
#pragma endregion

#pragma region setters
void SanityColor::SetR(unsigned int r) {
    if(r > 255) {
        throw SanityColor_InvalidColorParamException();
    } else {
        this->m_r = r;
    }
}

void SanityColor::SetG(unsigned int g) {
    if(g > 255) {
        throw SanityColor_InvalidColorParamException();
    } else {
        this->m_g = g;
    }
}

void SanityColor::SetB(unsigned int b) {
    if(b > 255) {
        throw SanityColor_InvalidColorParamException();
    } else {
        this->m_b = b;
    }
}

void SanityColor::SetA(float a) {
    if(a > 1) {
        throw SanityColor_InvalidColorParamException();
    } else {
        this->m_a = a;
    }
}
#pragma endregion
