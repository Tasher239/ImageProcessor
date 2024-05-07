#include <iostream>
#include <fstream>

#include "../../include/io/bmp.h"
#include "../../include/utils/exceptions.h"

void BMP::Save(const Image &image, const std::string &output_path) {
    int m_width = image.GetWidth();
    int m_height = image.GetHeight();

    std::cout << m_width << ' ' << m_height << '\n';

    std::ofstream f;
    f.open(output_path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        throw FileWriteError();
    }

    unsigned char bmp_pad[3] = {0, 0, 0};
    const int padding_amount = ((4 - (m_width * 3) % 4) % 4);
    const int file_header_size = 14;
    const int information_header_size = 40;
    const int file_size =
        file_header_size + information_header_size + m_width * m_height * 3 + padding_amount * m_height;

    unsigned char file_header[file_header_size];

    // file type
    file_header[0] = 'B';  // NOLINT
    file_header[1] = 'M';  // NOLINT

    // file size
    file_header[2] = file_size;        // NOLINT
    file_header[3] = file_size >> 8;   // NOLINT
    file_header[4] = file_size >> 16;  // NOLINT
    file_header[5] = file_size >> 24;  // NOLINT
    // reserved 1
    file_header[6] = 0;  // NOLINT
    file_header[7] = 0;  // NOLINT
    // reserved 2
    file_header[8] = 0;  // NOLINT
    file_header[9] = 0;  // NOLINT

    // pixel data offset
    file_header[10] = file_header_size + information_header_size;  // NOLINT
    file_header[11] = 0;                                           // NOLINT
    file_header[12] = 0;                                           // NOLINT
    file_header[13] = 0;                                           // NOLINT

    unsigned char information_header[information_header_size];  // NOLINT
    // header size
    information_header[0] = information_header_size;  // NOLINT
    information_header[1] = 0;                        // NOLINT
    information_header[2] = 0;                        // NOLINT
    information_header[3] = 0;                        // NOLINT

    // image width
    information_header[4] = m_width;        // NOLINT
    information_header[5] = m_width >> 8;   // NOLINT
    information_header[6] = m_width >> 16;  // NOLINT
    information_header[7] = m_width >> 24;  // NOLINT

    // image height
    information_header[8] = m_height;         // NOLINT
    information_header[9] = m_height >> 8;    // NOLINT
    information_header[10] = m_height >> 16;  // NOLINT
    information_header[11] = m_height >> 24;  // NOLINT

    // planes
    information_header[12] = 1;  // NOLINT
    information_header[13] = 0;  // NOLINT

    // bits per pixel (rgb)
    information_header[14] = 24;  // NOLINT
    information_header[15] = 0;   // NOLINT

    // compression (no)
    information_header[16] = 0;  // NOLINT
    information_header[17] = 0;  // NOLINT
    information_header[18] = 0;  // NOLINT
    information_header[19] = 0;  // NOLINT

    // image size (no compression)
    information_header[20] = 0;  // NOLINT
    information_header[21] = 0;  // NOLINT
    information_header[22] = 0;  // NOLINT
    information_header[23] = 0;  // NOLINT

    // x pixels per meter (no specified)
    information_header[24] = 0;  // NOLINT
    information_header[25] = 0;  // NOLINT
    information_header[26] = 0;  // NOLINT
    information_header[27] = 0;  // NOLINT

    // y pixels per meter (no specified)
    information_header[28] = 0;  // NOLINT
    information_header[29] = 0;  // NOLINT
    information_header[30] = 0;  // NOLINT
    information_header[31] = 0;  // NOLINT

    // total colors (color palette not used)
    information_header[32] = 0;  // NOLINT
    information_header[33] = 0;  // NOLINT
    information_header[34] = 0;  // NOLINT
    information_header[35] = 0;  // NOLINT

    // important colors (generally ignored)
    information_header[36] = 0;  // NOLINT
    information_header[37] = 0;  // NOLINT
    information_header[38] = 0;  // NOLINT
    information_header[39] = 0;  // NOLINT

    f.write(reinterpret_cast<char *>(file_header), file_header_size);
    f.write(reinterpret_cast<char *>(information_header), information_header_size);

    for (int i = m_height - 1; i > -1; i--) {
        for (int j = 0; j < m_width; j++) {

            unsigned char r = static_cast<unsigned char>(image[i][j].r * 255.0f);  // NOLINT
            unsigned char g = static_cast<unsigned char>(image[i][j].g * 255.0f);  // NOLINT
            unsigned char b = static_cast<unsigned char>(image[i][j].b * 255.0f);  // NOLINT

            unsigned char color[] = {b, g, r};
            f.write(reinterpret_cast<char *>(color), 3);
        }
        //         add padding in each row
        f.write(reinterpret_cast<char *>(bmp_pad), padding_amount);
    }

    f.close();

    std::cout << "File was created successfully!\n";
}

Image BMP::Load(const std::string &input_path) {
    std::ifstream f;
    f.open(input_path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        throw FileReadError();
    }
    const int file_header_size = 14;
    const int information_header_size = 40;

    unsigned char file_header[file_header_size];
    f.read(reinterpret_cast<char *>(file_header), file_header_size);

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        f.close();
        throw NotBMPError();
    }

    unsigned char information_header[information_header_size];
    f.read(reinterpret_cast<char *>(information_header), information_header_size);

    int m_width = information_header[4] + (information_header[5] << 8) + (information_header[6] << 16) +    // NOLINT
                  (information_header[7] << 24);                                                            // NOLINT
    int m_height = information_header[8] + (information_header[9] << 8) + (information_header[10] << 16) +  // NOLINT
                   (information_header[11] << 24);                                                          // NOLINT

    Image image(m_width, m_height);

    const int padding_amount = (4 - (m_width * 3) % 4) % 4;  // NOLINT

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            unsigned char color[3];
            f.read(reinterpret_cast<char *>(color), 3);                            // NOLINT
            image[m_height - y - 1][x].r = static_cast<float>(color[2]) / 255.0f;  // NOLINT
            image[m_height - y - 1][x].g = static_cast<float>(color[1]) / 255.0f;  // NOLINT
            image[m_height - y - 1][x].b = static_cast<float>(color[0]) / 255.0f;  // NOLINT
        }
        f.ignore(padding_amount);
    }
    f.close();
    std::cout << "File was read successfully!\n";

    return image;
}
