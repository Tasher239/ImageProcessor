#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <iostream>

#include "../filters/filter.h"
#include "exceptions.h"

class ArgsProcessor {
public:
    class FilterInfo {
    public:
        FilterInfo(std::string_view name, std::vector<std::string> &&params);

        std::string_view GetName() const;

        std::vector<std::string> GetParams() const;

    private:
        std::string name_;
        std::vector<std::string> params_;
    };

public:
    ArgsProcessor(int argc, char **argv) {
        if (argc < 3) {
            throw WrongAmountOfArguments(
                "{input file path} {output file path} [-{filter's name 1} [param 1] [param2 2] ...]", 3);
        }

        input_file_name_ = argv[1];
        output_file_name_ = argv[2];

        int i = 3;
        while (i < argc) {
            std::string name = argv[i];
            std::vector<std::string> params;
            i++;
            while (i < argc && argv[i][0] != '-') {
                params.emplace_back(argv[i]);
                ++i;
            }

            for (auto &x : params) {
                std::cout << x << '\n';
            }

            if (name == "-edge") {
                std::cout << "add filter: -gs" << '\n';
                filters_.emplace_back("-gs", std::vector<std::string>());
            }

            std::cout << "add filter: " << name << '\n';
            filters_.emplace_back(name, std::move(params));
        }
    }

    std::string GetInputFile() const;

    std::string GetOutputFile() const;

    const std::vector<FilterInfo> &GetFilters() const;

private:
    std::string input_file_name_;
    std::string output_file_name_;
    std::vector<FilterInfo> filters_;
};