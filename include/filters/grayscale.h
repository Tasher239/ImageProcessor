#pragma once

#include <vector>
#include <string>

#include "point_filter.h"
#include "../utils/abstract_filter_factory.h"

class GrayScale : public PointFilter {
public:
    Color Transform(const Color &pixel) override;

public:
    class Factory : public AbstractFilterFactory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string> &params) override {
            return std::make_unique<GrayScale>();
        };
    };
};
