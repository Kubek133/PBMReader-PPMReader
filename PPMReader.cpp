#include "PPMReader.h"
#include <sstream>
#include <algorithm>
#include <limits>

PPMReader::PPMReader(const std::string& imagePath) : imagePath(imagePath) {
    loadPPMImage();
}

PPMReader::~PPMReader() {
    if (imageFile.is_open()) {
        imageFile.close();
    }
}

void PPMReader::loadPPMImage() {
    imageFile.open(imagePath);
    if (!imageFile.is_open()) {
        std::cerr << "Error: The file could not be opened " << imagePath << std::endl;
        return;
    }

    std::string line;
    std::getline(imageFile, line);
    if (line != "P3") {
        std::cerr << "Error: Unsupported file format: " << line << std::endl;
        return;
    }

    // Skip comments
    while (std::getline(imageFile, line)) {
        if (line[0] != '#') {
            break;
        }
    }

    std::istringstream dimensionsStream(line);
    dimensionsStream >> width >> height;
    int maxValue;
    imageFile >> maxValue;

    imageData.resize(height, std::vector<int>(width * 3));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * 3; j += 3) {
            int r, g, b;
            imageFile >> r >> g >> b;
            imageData[i][j] = r;
            imageData[i][j + 1] = g;
            imageData[i][j + 2] = b;

            std::vector<int> color = { r, g, b };
            colorFrequencyMap[color]++;
        }
    }
}

void PPMReader::printImageInfo() {
    std::cout << "Image path: " << imagePath << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
}

void PPMReader::printMostFrequentColor() {
    auto mostFrequent = std::max_element(colorFrequencyMap.begin(), colorFrequencyMap.end(), [](const std::pair<std::vector<int>, int>& a, const std::pair<std::vector<int>, int>& b) {
        return a.second < b.second;
        });

    if (mostFrequent != colorFrequencyMap.end()) {
        std::cout << "The most common color: R=" << mostFrequent->first[0]
            << ", G=" << mostFrequent->first[1]
            << ", B=" << mostFrequent->first[2]
            << " (How many times did it repeat itself: " << mostFrequent->second << ")" << std::endl;
    }
    else {
        std::cout << "No colors found." << std::endl;
    }
}

int PPMReader::calculateNumberOfUniqueColors() {
    return colorFrequencyMap.size();
}