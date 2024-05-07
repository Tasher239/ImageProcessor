#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "point_filter.h"
#include "../utils/abstract_filter_factory.h"
#include "../utils/exceptions.h"

class Crop : public Filter {
public:
    Crop(int width, int height);

    Image Apply(const Image &image) override {
        int new_width = std::min(new_width_, image.GetWidth());
        int new_height = std::min(new_height_, image.GetHeight());

        Image cropped_image(new_width, new_height);

        for (int y = 0; y < new_height; ++y) {
            for (int x = 0; x < new_width; ++x) {
                cropped_image[y][x] = image[y][x];
            }
        }
        return cropped_image;
    }

private:
    int new_width_;
    int new_height_;

public:
    class Factory : public AbstractFilterFactory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string> &args) override {
            if (args.size() != 2) {
                throw WrongAmountOfFilterArguments("Crop", 2);
            }
            int new_width = std::stoi(args[0]);
            int new_height = std::stoi(args[1]);
            return std::make_unique<Crop>(new_width, new_height);
        };
    };
};
