#pragma once

#include "image_format.h"

class BMP : public ImageFormat {
public:
    void Save(const Image &image, const std::string &output_path) override;

    Image Load(const std::string &input_path) override;

private:
    struct FileHeader;
    struct BMPInfoHeader;
};