#include "../../include/filters/edge_detection.h"
#include "../../include/utils/exceptions.h"

EdgeDetection::EdgeDetection(float threshold) {
    threshold_ = threshold;
}

Color EdgeDetection::Transform(const Color &pixel, const std::vector<Color> &coord) {
    try {
        const Color &upper = coord[0];
        const Color &down = coord[1];
        const Color &left = coord[2];
        const Color &right = coord[3];
        const Color &center = coord[4];

        Color tmp = Color::Min(Color(1, 1, 1), Color::Max(Color(0, 0, 0), 4 * center - upper - down - left - right));

        if (tmp > threshold_) {
            tmp = {1, 1, 1};
        } else {
            tmp = {0, 0, 0};
        }
        return tmp;
    }

    catch (const std::exception &exception) {
        throw TransformError("Edge detection");
    }
}
