#include "../File/PNGFile.hpp"
#include "../Image/Image.hpp"
#include "../gaussian_blur.h"
#include "png.h"
#include <cstring>
#include <iostream>



std::vector<std::vector<t_Pixel>> PNGFile::read(Image& image) const {
    std::vector<std::vector<t_Pixel>> image_data;
    FILE* fp = fopen(filename_.c_str(), "rb");
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
    image.setWidth(png_get_image_width(png, info));
    image.setHeight(png_get_image_height(png, info));
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);
    if (color_type == PNG_COLOR_TYPE_RGB)
        png_set_add_alpha(png, 0xFF, PNG_FILLER_AFTER);
    png_read_update_info(png, info);
    std::vector<png_bytep> row_pointers(image.getHeight());
    for (int y = 0; y < image.getHeight(); ++y) {
        row_pointers[y] = new png_byte[png_get_rowbytes(png, info)];
    }
    png_read_image(png, row_pointers.data());
    for (int y = 0; y < image.getHeight(); ++y) {
        std::vector<t_Pixel> row_data(image.getWidth());
        for (int x = 0; x < image.getWidth(); ++x) {
            t_Pixel& pixel = row_data[x];
            png_byte* ptr = &(row_pointers[y][x * 4]); // Assuming RGBA format
            pixel.red = ptr[0];
            pixel.green = ptr[1];
            pixel.blue = ptr[2];
            pixel.alpha = ptr[3];
        }
        image_data.push_back(row_data);
    }
    png_destroy_read_struct(&png, &info, NULL);
    for (int y = 0; y < image.getHeight(); ++y) {
        delete[] row_pointers[y];
    }
    fclose(fp);
    return image_data;
}

void PNGFile::write(const Image& image) {
    const std::vector<std::vector<t_Pixel>>& pixels = image.getPixels();
    FILE* fp = fopen(filename_.c_str(), "wb");
    if (!fp) return ;
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) return ;
    png_infop info = png_create_info_struct(png);
    if (!info) return ;
    if (setjmp(png_jmpbuf(png))) return ;
    png_init_io(png, fp);
    std::vector<png_bytep> row_pointers;
    for (int y = 0; y < image.getHeight(); y++) {
        png_bytep row = new png_byte[image.getWidth() * sizeof(t_Pixel)];
        row_pointers.push_back(row);
        for (int x = 0; x < image.getWidth(); x++) {
            t_Pixel pixel = (pixels)[y][x];
            memcpy(&row[x * sizeof(t_Pixel)], &pixel, sizeof(t_Pixel));
        }
    }
    png_set_IHDR(
        png,
        info,
        image.getWidth(), image.getHeight(),
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