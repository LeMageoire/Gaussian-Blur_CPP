#ifndef PNGFILE_HPP
#define PNGFILE_HPP

#include "File.hpp"
#include <string>
#include "Image.hpp"

class PNGFile : public File {
public:
    PNGFile(const std::string& filename) : File(filename) {}

    std::vector<std::vector<t_Pixel>> read(Image& image) const override; 
    void write(const Image& image) override;
};

#endif // PNGFILE_HPP