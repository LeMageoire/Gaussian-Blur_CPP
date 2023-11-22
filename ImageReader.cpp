

template <typename ImageType>
class ImageReader {
    public:
        ImageReader(const std::string& filename);
        ImageType read();
    private:
        std::string filename_;
};

int main() {
    ImageReader<PNGImage> pngImageReader("image.png");
    PNGImage pngImage = pngImageReader.read();

    using GrayScaleImageReader = ImageReader<GrayscaleImageType>;
    ImageType grayscaleImage = GrayScaleImageReader("image.png").read();
    GaussianBlur<GrayscalePixelType, 3> blur;
    blur.apply(grayscaleImage);
}

