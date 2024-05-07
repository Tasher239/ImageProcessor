#pragma once

#include <concepts>
#include <vector>
#include <memory>
#include "../data/image.h"

class Filter {
public:
    Filter() = default;

    virtual ~Filter() = default;

    virtual Image Apply(const Image &image) = 0;
};

template <typename F>
concept FilterFactory = std::is_default_constructible_v<F> && std::invocable < F,
        const std::vector<std::string>
& > &&std::is_convertible_v<std::invoke_result_t<F, const std::vector<std::string> &>, std::unique_ptr<Filter>>;
