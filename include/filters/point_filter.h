#pragma once

#include "filter.h"

class PointFilter : public Filter {
    Image Apply(const Image &image) override;
    virtual Color Transform(const Color &pixel) = 0;
};