bool gaussianBlur(std::vector<std::vector<t_Pixel>>* inputImage, std::vector<std::vector<t_Pixel>>**  outputImage, int width, int height, int kernelSize, double sigma)
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
        // Create the output image
    *outputImage = new std::vector<std::vector<t_Pixel>>(height, std::vector<t_Pixel>(width));

    // Apply the kernel to each pixel in the input image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double red = 0.0, green = 0.0, blue = 0.0;
            for (int i = -halfSize; i <= halfSize; i++) {
                for (int j = -halfSize; j <= halfSize; j++) {
                    int xi = std::min(std::max(x + i, 0), width - 1);
                    int yj = std::min(std::max(y + j, 0), height - 1);
                    t_Pixel &pixel = (*inputImage)[yj][x];
                    red += pixel.red * kernel[i + halfSize][j + halfSize];
                    green += pixel.green * kernel[i + halfSize][j + halfSize];
                    blue += pixel.blue * kernel[i + halfSize][j + halfSize];
                }
            }
            (*(*outputImage))[y][x] = {static_cast<unsigned char>(red), static_cast<unsigned char>(green), static_cast<unsigned char>(blue), 255};
        }
    }

        return(true);
    }
}

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

void write_png_file(const char* file_name, int width, int height, std::vector<std::vector<t_Pixel>>* image_data) {
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
            png_bytep row = new png_byte[width * sizeof(t_Pixel)];
            row_pointers.push_back(row);
            for (int x = 0; x < width; x++) {
                t_Pixel pixel = (*image_data)[y][x];
                memcpy(&row[x * sizeof(t_Pixel)], &pixel, sizeof(t_Pixel));
            }
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
