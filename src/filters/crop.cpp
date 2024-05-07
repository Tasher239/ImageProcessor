#include "../../include/filters/crop.h"
#include "../../include/utils/exceptions.h"

Crop::Crop(int width, int height) {
    new_width_ = width;
    new_height_ = height;
}
