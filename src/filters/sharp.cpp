#include "../../include/filters/sharp.h"
#include <iostream>
#include "../../include/utils/exceptions.h"

Color Sharpening::Transform(const Color &pixel, const std::vector<Color> &coord) {
    try {
        const Color &upper = coord[0];   // NOLINT
        const Color &down = coord[1];    // NOLINT
        const Color &left = coord[2];    // NOLINT
        const Color &right = coord[3];   // NOLINT
        const Color &center = coord[4];  // NOLINT

        return Color::Min(Color(1, 1, 1),                                                         // NOLINT
                          Color::Max(Color(0, 0, 0), 5 * center - upper - down - left - right));  // NOLINT
    } catch (const std::exception &exception) {
        throw TransformError("Sharpening");
    }
}
