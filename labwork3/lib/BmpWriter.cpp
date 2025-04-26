#include "BmpWriter.h"
#include <fstream>
#include <array>

void BmpWriter::writeBMP(const std::string& filename, const std::vector<std::vector<uint64_t>>& field) {
    int height = field.size();
    int width = field[0].size();
    int rowSize = (3 * width + 3) & (~3);
    int dataSize = rowSize * height;
    int fileSize = 54 + dataSize;

    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("[ERROR] Can't open .bmp file");
    }

    std::array<uint8_t, 54> header = {
        'B','M',
        static_cast<uint8_t>(fileSize), static_cast<uint8_t>(fileSize >> 8),
        static_cast<uint8_t>(fileSize >> 16), static_cast<uint8_t>(fileSize >> 24),
        0,0, 0,0,
        54,0,0,0, 40,0,0,0,
        static_cast<uint8_t>(width), static_cast<uint8_t>(width >> 8),
        static_cast<uint8_t>(width >> 16), static_cast<uint8_t>(width >> 24),
        static_cast<uint8_t>(height), static_cast<uint8_t>(height >> 8),
        static_cast<uint8_t>(height >> 16), static_cast<uint8_t>(height >> 24),
        1,0, 24,0,
        0,0,0,0,
        static_cast<uint8_t>(dataSize), static_cast<uint8_t>(dataSize >> 8),
        static_cast<uint8_t>(dataSize >> 16), static_cast<uint8_t>(dataSize >> 24),
        0,0,0,0, 0,0,0,0,
        0,0,0,0, 0,0,0,0
    };

    file.write(reinterpret_cast<char*>(header.data()), header.size());

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            uint8_t r = 200, g = 200, b = 200;
            uint64_t value = field[y][x];

            if (value == 1) {
                r = 255; g = 215; b = 0;
            }
            else if (value == 2) {
                r = 220; g = 80;  b = 60;
            }
            else if (value == 3) {
                r = 70;  g = 130; b = 180;
            }
            else if (value > 3) {
                r = 50;  g = 50;  b = 50;
            }
            file.put(b).put(g).put(r);
        }
        for (int pad = 0; pad < rowSize - width * 3; ++pad)
            file.put(0);
    }
}
