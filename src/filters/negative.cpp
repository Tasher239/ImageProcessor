#include "../../include/filters/negative.h"
#include <iostream>
#include "../../include/utils/exceptions.h"

Color Negative::Transform(const Color &pixel) {
    try {
        Color new_pixel = Color(1.f, 1.f, 1.f) - pixel;
        return new_pixel;
    } catch (const std::exception &exception) {
        throw TransformError("Negative");
    }
}
