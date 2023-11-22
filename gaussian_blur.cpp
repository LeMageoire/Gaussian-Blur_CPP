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
#include "png.h"

extern "C" {
#include <zlib.h>
}

//#define COMPUTE_ON

namespace ImageProcessing{
/*
    void write_png_file(const char* file_name, int width, int height, const std::vector<std::vector<t_Pixel>>* image_data) {
        FILE* fp = fopen(file_name, "wb");
        if (!fp) return ;
        png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png) return ;
        png_infop info = png_create_info_struct(png);
        if (!info) return ;
        if (setjmp(png_jmpbuf(png))) return ;
        png_init_io(png, fp);
        std::vector<png_bytep> row_pointers;
        for (int y = 0; y < height; y++) {
            row_pointers.push_back(reinterpret_cast<png_bytep>(&image_data[y][0]));
        }
        png_set_IHDR(
            png,
            info,
            width, height,
            8, // bit depth
            PNG_COLOR_TYPE_RGBA,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT
        );
        png_write_info(png, info);
        png_write_image(png, row_pointers.data());
        png_write_end(png, NULL);
        fclose(fp);
        png_destroy_write_struct(&png, &info);
    }
*/
    std::vector<std::vector<t_Pixel>>* readPNG(const char* filename, int* width, int* height) {
        auto image_data = new std::vector<std::vector<t_Pixel>>;
        FILE* fp = fopen(filename, "rb");
        if (!fp) {
            std::cerr << "Error: Couldn't open PNG file." << std::endl;
            return image_data;
        }
        png_byte header[8];
        fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8)) {
            std::cerr << "Error: Not a valid PNG file." << std::endl;
            fclose(fp);
            return image_data;
        }
        png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png) {
            std::cerr << "Error: Couldn't create read struct." << std::endl;
            fclose(fp);
            return image_data;
        }
        png_infop info = png_create_info_struct(png);
        if (!info) {
            std::cerr << "Error: Couldn't create info struct." << std::endl;
            png_destroy_read_struct(&png, NULL, NULL);
            fclose(fp);
            return image_data;
        }
        if (setjmp(png_jmpbuf(png))) {
            std::cerr << "Error: Error during PNG file reading." << std::endl;
            png_destroy_read_struct(&png, &info, NULL);
            fclose(fp);
            return image_data;
        }
        png_init_io(png, fp);
        png_set_sig_bytes(png, 8);
        png_read_info(png, info);
        *width = png_get_image_width(png, info);
        *height = png_get_image_height(png, info);
        png_byte color_type = png_get_color_type(png, info);
        png_byte bit_depth = png_get_bit_depth(png, info);
        if (color_type == PNG_COLOR_TYPE_RGB)
            png_set_add_alpha(png, 0xFF, PNG_FILLER_AFTER);
        png_read_update_info(png, info);
        std::vector<png_bytep> row_pointers(*height);
        for (int y = 0; y < *height; ++y) {
            row_pointers[y] = new png_byte[png_get_rowbytes(png, info)];
        }
        png_read_image(png, row_pointers.data());

        for (int y = 0; y < *height; ++y) {
            std::vector<t_Pixel> row_data(*width);
            for (int x = 0; x < *width; ++x) {
                t_Pixel& pixel = row_data[x];
                png_byte* ptr = &(row_pointers[y][x * 4]); // Assuming RGBA format
                pixel.red = ptr[0];
                pixel.green = ptr[1];
                pixel.blue = ptr[2];
                pixel.alpha = ptr[3];
            }
            image_data->push_back(row_data);
        }
        png_destroy_read_struct(&png, &info, NULL);
        for (int y = 0; y < *height; ++y) {
            delete[] row_pointers[y];
        }
        fclose(fp);
        return image_data;
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
/*
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
*/
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
    
    std::vector<std::vector<t_Pixel> > * inputImage;
	std::vector<std::vector<t_Pixel> > * outputImage;
    int width;
    int height;
    //if(!lodepng::decode(inputImage, width, height, inputFilename))
    inputImage = ImageProcessing::readPNG(inputFilename.c_str(), &width, &height);
    if(inputImage == nullptr){
        std::cerr << "Error while reading PNG file" << std::endl;
        return EXIT_FAILURE;
    }
    #ifdef COMPUTE_ON
    if(!ImageProcessing::gaussianBlur(inputImage, outputImage, width, height, kernelSize, sigma))
    {
        std::cerr << "Error while blurring image" << std::endl;
        return EXIT_FAILURE;
    }
    #endif
    std::string outputFilename = inputFilename.substr(0, inputFilename.find_last_of('.')) + "_blurred.png";
    //ImageProcessing::write_png_file(outputFilename.c_str(), width, height, outputImage);
    /*{
        std::cerr << "Error while writing PNG file" << std::endl;
        return EXIT_FAILURE;
    }*/
    delete inputImage;
    return EXIT_SUCCESS;
}
