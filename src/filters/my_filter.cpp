#include "../../include/filters/my_filter.h"
#include "../../include/utils/exceptions.h"

//Для каждого пикселя (i, j) в матрице:
//- вычисляем сумму значений красного, зеленого и синего каналов пикселя
//- если сумма значений четная, то пиксель остается без изменений
//- Если сумма значений нечетная, то цвета меняются местами: красный -> зеленым, зеленый -> синим, синий -> красным

Color MyFilter::Transform(const Color &pixel) {
    try {
        auto r = static_cast<unsigned char>(pixel.r * 255.0f);  // NOLINT
        auto g = static_cast<unsigned char>(pixel.g * 255.0f);  // NOLINT
        auto b = static_cast<unsigned char>(pixel.b * 255.0f);  // NOLINT

        if ((r + g + b) % 2 == 0) {
            return pixel;
        }
        return {static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f,  // NOLINT
                static_cast<float>(r) / 255.0f};                                 // NOLINT
    } catch (const std::exception &exception) {
        throw TransformError("My filter");
    }
}
