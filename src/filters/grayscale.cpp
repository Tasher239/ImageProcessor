#include "../../include/filters/grayscale.h"
#include "../../include/utils/exceptions.h"

Color GrayScale::Transform(const Color &pixel) {
    try {
        auto new_color = static_cast<float>(0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);  // NOLINT
        return {new_color, new_color, new_color};
    } catch (const std::exception &exception) {
        throw TransformError("GreyScale");
    }
}
