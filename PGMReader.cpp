#include "PGMReader.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>

PGMReader::PGMReader(std::string filename) {

    name = filename;
    file.open(filename, std::ios::in);
    if (!file.good()) {
        std::cout << "Error: The file could not be opened" << filename << std::endl;
        return;
    }

    std::string formatIdentifier; 
    std::getline(file, formatIdentifier); 

    if (formatIdentifier != "P2") { 
        std::cout << "Error: Unsupported file format: " << formatIdentifier << std::endl;
        file.close();
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line[0] == '#')
            continue;
        std::istringstream iss(line);
        if (!(iss >> width >> height))
            break;
        break;
    }
    file >> maxColor;

    int pixel;
    while (file >> pixel) {
        pixels.push_back(pixel);
    }

    file.close();
}

PGMReader::~PGMReader()
{
    if (file.is_open())
    {
        file.close();
    }
}


void PGMReader::printImageInfo() {
    std::cout << "PGM Image Info: " << name << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Number of total pixels: " << width * height << std::endl;
    std::cout << "Maximum color value: " << maxColor << std::endl;
}

int PGMReader::calculateNumberOfUniqueColors() {
    std::map<int, int> colorCounts;
    for (int pixel : pixels) {
        colorCounts[pixel]++;
    }
    return colorCounts.size();
}

void PGMReader::printMostFrequentColor() {
    std::map<int, int> colorCounts;
    for (int pixel : pixels) {
        colorCounts[pixel]++;
    }
    if (!colorCounts.empty()) {
        auto maxColor = std::max_element(colorCounts.begin(), colorCounts.end(),
            [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
                return p1.second < p2.second;
            });
        std::cout << "The most common color: " << maxColor->first << " (Ilosc powtorzen: " << maxColor->second << ")" << std::endl;
    }
    else {
        std::cout << "No colors found." << std::endl;
    }
}
