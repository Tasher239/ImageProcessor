#pragma once

#include "filter.h"

class MatrixFilter : public Filter {
    Image Apply(const Image &image) override;

    virtual Color Transform(const Color &pixel, const std::vector<Color> &coord) = 0;
};