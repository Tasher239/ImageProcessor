#include "../../include/data/color.h"
#include <algorithm>

Color::Color() : r(0), g(0), b(0) {
}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {
}

Color::~Color() {
}

Color &Color::operator=(const Color &other) {
    if (this != &other) {
        r = other.r;
        g = other.g;
        b = other.b;
    }
    return *this;
}

Color Color::operator+(const Color &other) const {
    return {r + other.r, g + other.g, b + other.b};
}

Color Color::operator-(const Color &other) const {
    return {r - other.r, g - other.g, b - other.b};
}

Color Color::operator/(float scalar) const {
    if (scalar != 0) {
        return {r / scalar, g / scalar, b / scalar};
    } else {
        //        деление на 0!?!?
        return Color();
    }
}

Color &Color::operator+=(const Color &other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

Color &Color::operator-=(const Color &other) {
    if (this != &other) {
        r = other.r;
        g = other.g;
        b = other.b;
    }
    return *this;
}

Color &Color::operator*=(float scalar) {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    return *this;
}

float Color::GetColor(int y, int x) const {
    return r + g + b;
}

Color Color::operator-() const {
    return Color(-r, -g, -b);
}

Color Color::operator*(float scalar) const {
    return Color(r * scalar, g * scalar, b * scalar);
}

Color operator*(float scalar, const Color &color) {
    return Color(color.r * scalar, color.g * scalar, color.b * scalar);
}

Color Color::Max(const Color &a, const Color &b) {
    return Color(std::max(a.r, b.r), std::max(a.g, b.g), std::max(a.b, b.b));
}

Color Color::Min(const Color &a, const Color &b) {
    return Color(std::min(a.r, b.r), std::min(a.g, b.g), std::min(a.b, b.b));
}

bool operator<(const Color &color, float scalar) {
    return (color.r < scalar && color.g < scalar && color.b < scalar);
}

bool operator<(float scalar, const Color &color) {
    return (scalar < color.r && scalar < color.g && scalar < color.b);
}

bool operator>(const Color &color, float scalar) {
    return (color.r > scalar && color.g > scalar && color.b > scalar);
}

bool operator>(float scalar, const Color &color) {
    return (scalar > color.r && scalar > color.g && scalar > color.b);
}
