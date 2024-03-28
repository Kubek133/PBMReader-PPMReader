#include "PGMReader.h"
#include "PPMReader.h"

int main() {
    PGMReader r_pgm("screws.pgm");
    ImageReader* reader_pgm = &r_pgm;

    r_pgm.printImageInfo();
    std::cout << "Number of different colors: " << r_pgm.calculateNumberOfUniqueColors() << std::endl;
    r_pgm.printMostFrequentColor();

    PPMReader r_ppm("starfield.ppm");
    ImageReader* reader_ppm = &r_ppm;

    r_ppm.printImageInfo();
    std::cout << "Number of different colors: " << r_ppm.calculateNumberOfUniqueColors() << std::endl;
    r_ppm.printMostFrequentColor();

    return 0;
}
