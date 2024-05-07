#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "point_filter.h"
#include "../utils/abstract_filter_factory.h"

//смотрим эл-ты на расстоянии не дальше 3сигма
class GaussianBlur : public Filter {
public:
    explicit GaussianBlur(float sigma);

    static std::vector<Color> HorizontalBlur(const std::vector<Color> &line, float sigma);

    static Image Transpose(const Image &image);

    Image Apply(const Image &image) override {
        int width = image.GetWidth();
        int height = image.GetHeight();

        Image horizontal_blur_image{width, height};
        for (int i = 0; i < horizontal_blur_image.GetHeight(); ++i) {
            horizontal_blur_image.SetRow(i, HorizontalBlur(image[i], sigma_));
        }

        Image transposed_horizontal_blur_image;
        transposed_horizontal_blur_image = Transpose(horizontal_blur_image);

        for (int i = 0; i < transposed_horizontal_blur_image.GetHeight(); ++i) {
            transposed_horizontal_blur_image.SetRow(i, HorizontalBlur(transposed_horizontal_blur_image[i], sigma_));
        }

        Image vertical_horizontal_blur_image;
        vertical_horizontal_blur_image.SetColors(Transpose(transposed_horizontal_blur_image).GetColors());

        return vertical_horizontal_blur_image;
    }

private:
    float sigma_;

public:
    class Factory : public AbstractFilterFactory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string> &args) override {
            return std::make_unique<GaussianBlur>(std::stof(args[0]));
        };
    };
};
