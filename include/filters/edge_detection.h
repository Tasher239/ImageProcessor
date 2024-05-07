#pragma once

#include <vector>
#include <string>

#include "point_filter.h"
#include "../utils/abstract_filter_factory.h"
#include "grayscale.h"
#include "matrix_filter.h"

class EdgeDetection : public MatrixFilter {
public:
    explicit EdgeDetection(float threshold);

    Color Transform(const Color &pixel, const std::vector<Color> &coord) override;

private:
    float threshold_;

public:
    class Factory : public AbstractFilterFactory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string> &args) override {
            return std::make_unique<EdgeDetection>(std::stof(args[0]));
        };
    };
};
