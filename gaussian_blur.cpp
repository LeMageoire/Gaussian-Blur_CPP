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

#include "gaussian_blur.h"
//#include "third-party/lodepng/lodepng.h"
#include <png.h>

extern "C" {
#include <zlib.h>
}


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

bool gaussianBlur(const std::vector<t_Pixel>& inputImage, std::vector<t_Pixel>& outputImage, int width, int height, int kernelSize, double sigma)
{
    int halfSize = kernelSize / 2;

    std::vector<std::vector<double> > kernel(kernelSize, std::vector<double>(kernelSize, 0.0));
    double sum = 0.0;

    for (int i= -halfSize; i<= halfSize; ++i)
    {
        for(int j = -halfSize; j <= halfSize; ++j)
        {
            double value = std::exp(-(i*i + j*j) / (2*sigma*sigma)) / (2*M_PI*sigma*sigma);
            kernel[i + halfSize][j + halfSize] = value;
            sum += value;
        }
    }

    for(int i = 0; i < kernelSize; ++i)
    {
        for(int j = 0; j < kernelSize; ++j)
        {
            kernel[i][j] /= sum;
        }
    }

    std::vector<t_Pixel> tempImage(width * height);

    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j) 
        {
            double red = 0.0, green = 0.0, blue = 0.0;
            for(int k = -halfSize; k <= halfSize; ++k)
            {
                for(int l = -halfSize; l <= halfSize; ++l)
                {
                    int x = std::min(std::max(j + l, 0), width - 1);
                    int y = std::min(std::max(i + k, 0), height - 1);
                    red += inputImage[y * width + x].red * kernel[k + halfSize][l + halfSize];
                    green += inputImage[y * width + x].green * kernel[k + halfSize][l + halfSize];
                    blue += inputImage[y * width + x].blue * kernel[k + halfSize][l + halfSize];
                }
            }
            tempImage[i * width + j].red = red;
            tempImage[i * width + j].green = green;
            tempImage[i * width + j].blue = blue;
        }
    }
    outputImage = tempImage;
    return(true);
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

    if((kernelSize & 1) == 0){
        std::cerr << "Kernel size must be odd" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::vector<t_Pixel> inputImage;
	std::vector<t_Pixel> outputImage;
    int width, height;
    if(!lodepng::decode(inputImage, width, height, inputFilename))
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
    if(!lodepng::encode(outputFilename, outputImage, width, height))
    {
        std::cerr << "Error while writing PNG file" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
