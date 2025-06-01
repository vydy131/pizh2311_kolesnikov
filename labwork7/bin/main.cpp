#include <fstream>
#include "lib//MetaDecoder.h"

int main() {
    std::ifstream file("/home/vydy131/CLionProjects/pizh2311_kolesnikov/labwork7/tests/U96 - Das Boot.mp3", std::ios::binary);
    if (!file) {
        std::cerr << "File not found!" << std::endl;
        return 1;
    }

    // Чтение заголовка
    char header[10];
    file.read(header, 10);
    if (std::string(header, 3) != "ID3") {
        std::cerr << "Not an ID3v2 tag" << std::endl;
        return 1;
    }

    // Размер тега
    uint32_t tagSize = static_cast<uint8_t>(header[6]) << 21 |
                       static_cast<uint8_t>(header[7]) << 14 |
                       static_cast<uint8_t>(header[8]) << 7 |
                       static_cast<uint8_t>(header[9]);

    // Обработка
    BlockProcessor processor;
    parseMetadataBlocks(file, tagSize, processor);

    return 0;
}