#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include "point_filter.h"
#include "../utils/abstract_filter_factory.h"
#include "../utils/exceptions.h"

// принимаем диапазон смещения

class GlassDistortion : public Filter {
public:
    GlassDistortion(int min_delta, int max_delta);

    Image Apply(const Image &image) override {
        int width = image.GetWidth();
        int height = image.GetHeight();
        Image distorted_image(width, height);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(min_delta_, max_delta_);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int offsetX = distribution(gen);
                int offsetY = distribution(gen);

                int newX = std::max(0, std::min(width - 1, x + offsetX));
                int newY = std::max(0, std::min(height - 1, y + offsetY));

                distorted_image[y][x] = image[newY][newX];
            }
        }
        return distorted_image;
    }

private:
    int min_delta_;
    int max_delta_;

public:
    class Factory : public AbstractFilterFactory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string> &args) override {
            if (args.size() < 2) {
                throw WrongAmountOfFilterArguments("Glass distortion", 2);
            }
            return std::make_unique<GlassDistortion>(std::stoi(args[0]), std::stoi(args[1]));
        };
    };
};
