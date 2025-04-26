#include <iostream>
#include <filesystem>
#include <string>
#include <cstdint>
#include "Sandpile.h"

void printHelp(const char* programName) {
    std::cerr << "Usage: " << programName << " [OPTIONS]\n"
              << "Options:\n"
              << "  -l, --length <value>  Sandpile height (uint16_t)\n"
              << "  -w, --width  <value>  Sandpile width (uint16_t)\n"
              << "  -i, --input  <file>   Input TSV file\n"
              << "  -h, --help            Show this help message\n";
}

int main(int argc, char* argv[]) {
    uint16_t width = 0, height = 0;
    std::string inputFile;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            printHelp(argv[0]);
            return 0;
        }
        else if (arg == "-l" || arg == "--length") {
            if (i + 1 >= argc) {
                std::cerr << "[ERROR] Missing value for " << arg << "\n";
                return 1;
            }
            height = static_cast<uint16_t>(std::stoi(argv[++i]));
        }
        else if (arg == "-w" || arg == "--width") {
            if (i + 1 >= argc) {
                std::cerr << "[ERROR] Missing value for " << arg << "\n";
                return 1;
            }
            width = static_cast<uint16_t>(std::stoi(argv[++i]));
        }
        else if (arg == "-i" || arg == "--input") {
            if (i + 1 >= argc) {
                std::cerr << "[ERROR] Missing filename for " << arg << "\n";
                return 1;
            }
            inputFile = argv[++i];
        }
        else {
            std::cerr << "[ERROR] Unknown argument '" << arg << "'\n";
            printHelp(argv[0]);
            return 1;
        }
    }

    if (width == 0 || height == 0 || inputFile.empty()) {
        std::cerr << "[ERROR] Missing required arguments!\n";
        printHelp(argv[0]);
        return 1;
    }

    try {
        if (!std::filesystem::exists(inputFile)) {
            std::cerr << "[ERROR] No file " << inputFile << std::endl;
            return 1;
        }

        Sandpile pile(width, height);
        pile.loadFromFile(inputFile);
        pile.run(100000, 0, inputFile);

        std::cout << "[INFO] Run is over. Result in main_input.bmp\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << "\n";
        return 1;
    }

    return 0;
}