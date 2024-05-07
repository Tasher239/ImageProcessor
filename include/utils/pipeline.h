#pragma once

#include "memory"
#include "string_view"
#include "unordered_map"
#include "functional"
#include "string"
#include "../filters/filter.h"
#include "../data/image.h"

class Pipeline {
public:
    class Factory {
    public:
        template <FilterFactory F>
        void RegisterFilter(std::string_view name) {
            factrories_.emplace(name, [factory = F{}](const std::vector<std::string> &parameters) mutable {
                return factory(parameters);
            });
        };

        std::unique_ptr<Filter> CreateFilter(std::string_view name, const std::vector<std::string> &params);

    private:
        // словарь функций констракт для каждого фильтра
        std::unordered_map<std::string, std::function<std::unique_ptr<Filter>(const std::vector<std::string> &)>>
            factrories_;
    };

public:
    void AddFilter(std::unique_ptr<Filter> &&filter);

    Image Process(const Image &image);

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};