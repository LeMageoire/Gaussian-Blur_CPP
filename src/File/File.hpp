#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>
#include "../gaussian_blur.h"

class Image;

class File {
public:
    File(const std::string& filename) : filename_(filename) {}
 
    virtual std::vector<std::vector<t_Pixel> > read() const = 0;

    virtual void write(const Image& image) = 0;

protected:
    std::string filename_;
};

#endif // FILE_HPP