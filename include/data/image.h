#pragma once

#include "color.h"
#include <vector>

class Image {
public:
    Image(int width, int height);

    Image() = default;

    ~Image();

    Color GetColor(int y, int x) const;

    int GetWidth() const;

    int GetHeight() const;

    std::vector<Color> &operator[](int index);

    const std::vector<Color> &operator[](int index) const;

    void SetRow(int index, const std::vector<Color> &row_colors);
    std::vector<Color> GetRow(int index);

    void SetColors(const std::vector<std::vector<Color>> &colors);

    std::vector<std::vector<Color>> GetColors();

private:
    int width_;
    int height_;
    std::vector<std::vector<Color>> colors_;
};
