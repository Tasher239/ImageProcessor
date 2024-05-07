#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../filters/filter.h"

class AbstractFilterFactory {
public:
    AbstractFilterFactory() = default;

    virtual ~AbstractFilterFactory() = default;

    std::unique_ptr<Filter> operator()(const std::vector<std::string> &params) {
        return Construct(params);
    }

    virtual std::unique_ptr<Filter> Construct(const std::vector<std::string> &params) = 0;
};