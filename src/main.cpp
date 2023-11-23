
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include <algorithm>

#include "./Kernel/Kernel.hpp"
#include "./Image/Image.hpp"
#include "gaussian_blur.h"
//#include "./File/File.hpp"
#include "./File/PNGFile.hpp"

int main(int argc, char *argv[]) {
    if (argc != EXPECTED_ARGUMENTS)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> <sigma>" << std::endl;
        return EXIT_FAILURE;
    }
    std::string inputFilename = argv[ARG_INPUT_FILE];
    int kernelSize = std::atoi(argv[ARG_KERNEL_SIZE]);
    double sigma = std::atof(argv[ARG_SIGMA]);

    if((kernelSize & 1) == 0){
        std::cerr << "Kernel size must be odd" << std::endl;
        return EXIT_FAILURE;
    }
    PNGFile Pf1(inputFilename);
    Image im1(Pf1);
    GaussianKernel<double> GaussianKernel(kernelSize, sigma);
    im1.filter(GaussianKernel);
    std::string outputFilename = inputFilename.substr(0, inputFilename.find_last_of('.')) + "_blurred.png";
    PNGFile Pf2(outputFilename);
    Pf2.write(im1);
    return EXIT_SUCCESS;
}