#include "../../include/filters/point_filter.h"
#include <iostream>
#include <vector>

Image PointFilter::Apply(const Image &image) {
    Image new_image = image;
    for (int i = 0; i < image.GetHeight(); i++) {
        for (int j = 0; j < image.GetWidth(); j++) {
            new_image[i][j] = Transform(new_image[i][j]);
        }
    }
    return new_image;
}
