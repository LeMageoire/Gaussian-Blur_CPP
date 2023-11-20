/**
 * @file main.cpp
 * @author Mathis Guyot (mathis.guyot@hotmail.com)
 * @brief my implementation of Gaussian Blur for 2D images
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include <algorithm>


#define EXPECTED_ARGUMENTS (4)
#define ARG_INPUT_FILE (1)
#define ARG_KERNEL_SIZE (2)
#define ARG_SIGMA (3)

typedef struct s_Pixel {
    unsigned char red, green, blue;
} t_Pixel;

/**
 * @brief 
 * 
 * @param inputImage 
 * @param outputImage 
 * @param width 
 * @param height 
 * @param kernelSize 
 * @param sigma 
 */

void gaussianBlur(const std::vector<Pixel>& inputImage, std::vector<Pixel>& outputImage, int width, int height, int kernelSize, double sigma)
{
    // TODO
}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char *argv[]){
    if (argc != EXPECTED_ARGUMENTS)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> <sigma>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputFilename = argv[ARG_INPUT_FILE];
    int kernelSize = std::atoi(argv[ARG_KERNEL_SIZE]);
    double sigma = std::atof(argv[ARG_SIGMA]);

    if(kernelSize & 1 == 0){
        std::cerr << "Kernel size must be odd" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::vector<Pixel> inputImage, outputImage;
    int width, height;
    if(!readPNG())
    {
        std::cerr << "Error while reading PNG file" << std::endl;
        return EXIT_FAILURE;
    }
    if(!gaussianBlur(inputImage, outputImage, width, height, kernelSize, sigma))
    {
        std::cerr << "Error while blurring image" << std::endl;
        return EXIT_FAILURE;
    }
    std::string outputFilename = inputFilename.substr(0, inputFilename.find_last_of('.')) + "_blurred.png";
    if(!writePNG(outputFilename, outputImage, width, height))
    {
        std::cerr << "Error while writing PNG file" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}