#ifndef _PGM_READER_HPP_
#define _PGM_READER_HPP_

#include "ImageReader.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>

class PGMReader : public ImageReader {
private:
    int width;
    int height;
    int maxColor;
    std::vector<int> pixels;
    std::string name;
    std::fstream file;

public:
    PGMReader(const std::string filename);
    ~PGMReader();
    virtual void printImageInfo() override;
    virtual int calculateNumberOfUniqueColors() override;
    virtual void printMostFrequentColor() override;
};

#endif