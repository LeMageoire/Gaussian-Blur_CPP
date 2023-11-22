


template <typename PixelType>
class Image {
    public:
        Image()

    private:
        int width_;
        int height_;
        std::vector<PixelType> data_;
};

template <typename ImageType>
class ImageReader {
    public:
        ImageReader(const std::string& filename) : filename_(filename) {}
    
    private :
        std::string filename_;

}

template <typename PixelType>
void gaussianblur(Image<PixelType>& image){
    
}

int main(int argc, char *argv[]) {
    if (argc != EXPECTED_ARGUMENTS)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> <sigma>" << std::endl;
        return EXIT_FAILURE;
    }
    if((kernelSize & 1) == 0){
        std::cerr << "Kernel size must be odd" << std::endl;
        return EXIT_FAILURE;
    }
    std::string inputFilename = argv[ARG_INPUT_FILE];
    int kernelSize = std::atoi(argv[ARG_KERNEL_SIZE]);
    double sigma = std::atof(argv[ARG_SIGMA]);
    ImageReader<Image<unsigned char>> imageReader(inputFilename.c_str());
    auto image = imageReader.read();
    gaussianblur(*image);

    std::string outputFilename = inputFilename.substr(0, inputFilename.find_last_of('.')) + "_blurred.png";
    ImageWriter<Image<unsigned char>> imageWriter(outputFilename.c_str());

    return EXIT_SUCCESS;
}