#include "../../include/utils/pipeline.h"
#include "../../include/utils/exceptions.h"

std::unique_ptr<Filter> Pipeline::Factory::CreateFilter(const std::string_view name,
                                                        const std::vector<std::string> &params) {
    auto it = factrories_.find(name.data());
    if (it != factrories_.end()) {
        return it->second(params);
    } else {
        throw WrongFilterName(it->first);
    }
}

void Pipeline::AddFilter(std::unique_ptr<Filter> &&filter) {
    filters_.emplace_back(std::move(filter));
}

Image Pipeline::Process(const Image &image) {
    Image result_image = image;
    for (const auto &filter : filters_) {
        result_image = filter->Apply(result_image);
    }
    return result_image;
}