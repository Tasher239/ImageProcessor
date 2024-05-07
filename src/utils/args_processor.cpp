#include "../../include/utils/args_processor.h"

ArgsProcessor::FilterInfo::FilterInfo(std::string_view name, std::vector<std::string> &&params) {
    name_ = name;
    params_ = params;
}

std::string_view ArgsProcessor::FilterInfo::GetName() const {
    return name_;
}

std::vector<std::string> ArgsProcessor::FilterInfo::GetParams() const {
    return params_;
}

std::string ArgsProcessor::GetInputFile() const {
    return input_file_name_;
}

std::string ArgsProcessor::GetOutputFile() const {
    return output_file_name_;
}

const std::vector<ArgsProcessor::FilterInfo> &ArgsProcessor::GetFilters() const {
    return filters_;
}
