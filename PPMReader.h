#ifndef PPMREADER_HPP
#define PPMREADER_HPP

#include "ImageReader.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

class PPMReader : public ImageReader {
public:
    PPMReader(const std::string& imagePath);
    ~PPMReader();

    void printImageInfo() override;
    void printMostFrequentColor() override;
    int calculateNumberOfUniqueColors() override;

private:
    std::ifstream imageFile;
    std::vector<std::vector<int>> imageData;
    int width, height;
    std::string imagePath;

    void loadPPMImage();
    std::map<std::vector<int>, int> colorFrequencyMap;
};

#endif // PPMREADER_HPP