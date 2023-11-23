

#include "Kernel.hpp"
#include "gaussian_blur.h"

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
    std::vector<std::vector<t_Pixel> > * inputImage;
	std::vector<std::vector<t_Pixel> > * outputImage;
    int width;
    int height;

    inputImage = ImageProcessing::readPNG(inputFilename.c_str(), &width, &height);
    if(inputImage == nullptr){
        std::cerr << "Error while reading PNG file" << std::endl;
        return EXIT_FAILURE;
    }
    
    GaussianKernel<double> kernel(kernelSize, sigma);
    kernel.fill();
    image.filter(kernel);

    std::string outputFilename = inputFilename.substr(0, inputFilename.find_last_of('.')) + "_blurred.png";
    ImageProcessing::write_png_file(outputFilename.c_str(), width, height, outputImage);

    return EXIT_SUCCESS;
}