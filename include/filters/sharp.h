#pragma once

#include <vector>
#include <string>

#include "point_filter.h"
#include "../utils/abstract_filter_factory.h"
#include "matrix_filter.h"

class Sharpening : public MatrixFilter {
public:
    Color Transform(const Color &pixel, const std::vector<Color> &coord) override;

public:
    class Factory : public AbstractFilterFactory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string> &) override {
            return std::make_unique<Sharpening>();
        };
    };
};
