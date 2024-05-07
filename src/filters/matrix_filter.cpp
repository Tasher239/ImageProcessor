#include "../../include/filters/matrix_filter.h"

Image MatrixFilter::Apply(const Image &image) {
    Color upper;
    Color down;
    Color left;
    Color right;
    Color center;

    Image new_image = image;
    for (int i = 0; i < image.GetHeight(); i++) {
        for (int j = 0; j < image.GetWidth(); j++) {
            if (i == 0) {
                upper = image[i][j];
            } else {
                upper = image[i - 1][j];
            }
            if (i == image.GetHeight() - 1) {
                down = image[i][j];
            } else {
                down = image[i + 1][j];
            }
            if (j == 0) {
                left = image[i][j];
            } else {
                left = image[i][j - 1];
            }
            if (j == image.GetWidth() - 1) {
                right = image[i][j];
            } else {
                right = image[i][j + 1];
            }
            center = image[i][j];
            new_image[i][j] = Transform(new_image[i][j], std::vector{upper, down, left, right, center});
        }
    }

    return new_image;
}
