#include <iostream>
#include <png.h>

extern "C" {
#include <zlib.h>
}

void read_png_file(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) abort();

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();

    png_infop info = png_create_info_struct(png);
    if (!info) abort();

    if (setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    std::cout << "Width: " << width << ", Height: " << height << std::endl;
    std::cout << "Color type: " << static_cast<int>(color_type) << ", Bit depth: " << static_cast<int>(bit_depth) << std::endl;

    png_bytep row_pointers[height];
    for (int y = 0; y < height; y++)
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));

    png_read_image(png, row_pointers);

    fclose(fp);

    for (int y = 0; y < height; y++)
        free(row_pointers[y]);
}

int main() {
    const char *filename = "./files/Lenna_(test_image).png";
    read_png_file(filename);

    return 0;
}

