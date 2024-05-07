#include "../../include/data/image.h"
#include <iostream>
#include <fstream>

Image::Image(int width, int height) : width_(width), height_(height), colors_(height, std::vector<Color>(width)) {
}

Image::~Image() {
}

Color Image::GetColor(int y, int x) const {
    return colors_[y][x];
}

int Image::GetWidth() const {
    return width_;
}

int Image::GetHeight() const {
    return height_;
}

std::vector<Color> &Image::operator[](int index) {
    return colors_[index];
}

const std::vector<Color> &Image::operator[](int index) const {
    return colors_[index];
}

void Image::SetRow(int index, const std::vector<Color> &row_colors) {
    colors_[index] = row_colors;
}

std::vector<Color> Image::GetRow(int index) {
    return colors_[index];
}

void Image::SetColors(const std::vector<std::vector<Color>> &colors) {
    colors_ = colors;
    width_ = static_cast<int>(colors_[0].size());
    height_ = static_cast<int>(colors_.size());
}

std::vector<std::vector<Color>> Image::GetColors() {
    return colors_;
}
