#include <cmath>
#include "../../include/filters/gaussian_blur.h"

GaussianBlur::GaussianBlur(float sigma) {
    sigma_ = sigma;
}

Image GaussianBlur::Transpose(const Image &image) {
    Image transposed_image(image.GetHeight(), image.GetWidth());

    for (int i = 0; i < image.GetHeight(); i++) {
        for (int j = 0; j < image.GetWidth(); j++) {
            transposed_image[j][i] = image[i][j];
        }
    }
    return transposed_image;
}

std::vector<Color> GaussianBlur::HorizontalBlur(const std::vector<Color> &line, float sigma) {
    int size = static_cast<int>(line.size());
    std::vector<Color> result(size);

    int delta = static_cast<int>(std::ceil(3 * sigma));

    Color ans;
    for (int pixel_ind = 0; pixel_ind < size; ++pixel_ind) {
        int left_border = pixel_ind - delta;
        int right_border = pixel_ind + delta;
        ans = {0, 0, 0};
        for (int i = left_border; i < right_border; ++i) {
            auto dif_pos = static_cast<float>(pixel_ind - i);
            if (i < 0) {
                ans += line[0] * std::exp(-(dif_pos * dif_pos) / (2 * sigma * sigma));  // NOLINT
            } else if (i >= size) {
                ans += line[size - 1] * std::exp(-(dif_pos * dif_pos) / (2 * sigma * sigma));  // NOLINT
            } else {
                ans += line[i] * std::exp(-(dif_pos * dif_pos) / (2 * sigma * sigma));  // NOLINT
            }
        }
        ans *= 0.39894 / sigma;  // NOLINT
        result[pixel_ind] = ans;
    }
    return result;
}
