#pragma once

class Color {
public:
    float r, g, b;

    Color();

    Color(float r, float g, float b);

    ~Color();

    Color &operator=(const Color &other);

    Color operator+(const Color &other) const;

    Color operator-(const Color &other) const;

    friend Color operator*(float scalar, const Color &color);

    Color operator*(float scalar) const;

    Color operator/(float scalar) const;

    Color &operator+=(const Color &other);

    Color &operator-=(const Color &other);

    Color &operator*=(float scalar);

    Color operator-() const;

    float GetColor(int y, int x) const;

    static Color Max(const Color &a, const Color &b);

    static Color Min(const Color &a, const Color &b);

    friend bool operator<(const Color &color, float scalar);

    friend bool operator<(float scalar, const Color &color);

    friend bool operator>(const Color &color, float scalar);

    friend bool operator>(float scalar, const Color &color);
};