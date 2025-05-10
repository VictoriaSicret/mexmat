#include "Image.hpp"

Pixel::Pixel(const double& r = 0, const double& g = 0, const double& b = 0) : r(r), g(g), b(b) {}

Pixel::~Pixel(){}

Image::Image(const size_t& width, const size_t& height, size_t px_sz) : width(width), height(height), pixels(std::vector<Pixel>(width * height)) {}

Image::~Image() {}

Pixel Image::GetPixel(const size_t& x, const size_t& y) const {return pixels[y*width+x];}

void Image::SetPixel(const Pixel& pixel, const size_t& x, const size_t& y) {
    pixels[y*width+x].r = pixel.r;
    pixels[y*width+x].g = pixel.g;
    pixels[y*width+x].b = pixel.b;
}

void Image::Read(const char* filename) {
    std::ifstream f;
    f.open(filename, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "Error: file could not be opened " << std::endl;
		return;
    }

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M') {
        std::cout << "Error: file is not a BMP file " << std::endl;
        f.close();
        return;
    }

    unsigned char informationHeader[informationHeaderSize];
    f.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);
	const int sd = fileHeader[10] + (fileHeader[11] << 8) + (fileHeader[12] << 16) + (fileHeader[13] << 24);

    f.close();


    f.open(filename, std::ios::in | std::ios::binary);

    f.ignore(sd);

    pixels.resize(width * height);

    const int paddingAmount = ((4 - (width * 3) % 4) % 4);
    pixel_size = informationHeader[14] / 8;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (pixel_size == 3) {
                unsigned char color[3];
                f.read(reinterpret_cast<char*>(color), 3);

                pixels[y * width + x].r = static_cast<float>(color[2]) / 255.0f;
                pixels[y * width + x].g = static_cast<float>(color[1]) / 255.0f;
                pixels[y * width + x].b = static_cast<float>(color[0]) / 255.0f;
            } else if (m_pixel_size == 4) {
                unsigned char color[4];
                f.read(reinterpret_cast<char*>(color), 4);

                pixels[y * width + x].r = static_cast<float>(color[2]) / 255.0f;
                pixels[y * width + x].g = static_cast<float>(color[1]) / 255.0f;
                pixels[y * width + x].b = static_cast<float>(color[0]) / 255.0f;
            }
        }

        f.ignore(paddingAmount);
    }

    f.close();

    std::cout << "File read" << std::endl;
}

void Image::Export(const char* filename) {
    std::ofstream f;
    f.open(filename, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std :: cout << "Error: file could not be opened " << std :: endl;
        return;
    }

    unsigned char bmpPad[3] = {0, 0, 0};
    const int paddingAmount = ((4 - (width * 3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize = fileHeaderSize + informationHeaderSize + (width * height * 3) + (paddingAmount * width);

    unsigned char fileHeader[fileHeaderSize];

    // File type 
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    // File size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    // Reserved (not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    fileHeader[8] = 0;
    fileHeader[9] = 0;

    // Pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    // Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    // Image width
    informationHeader[4] = width;
    informationHeader[5] = width >> 8;
    informationHeader[6] = width >> 16;
    informationHeader[7] = width >> 24;

    // Image height
    informationHeader[8] = height;
    informationHeader[9] = height >> 8;
    informationHeader[10] = height >> 16;
    informationHeader[11] = height >> 24;

    // Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;

    // Bits per pixel (RGB)
    informationHeader[14] = pixel_size * 8;
    informationHeader[15] = 0;

    // Compression (no compression)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;

    // Image size (no compression)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;

    // X pixels per meter (not specified)
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;

    // Y pixels per meter (not specified)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;

    // Yotal colors (color palette not used)
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;

    // Important colors (all colors are important)
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (pixel_size == 3) {
                unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);
                unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
                unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);

                unsigned char color[] = {b, g, r};

		        f.write(reinterpret_cast<char*>(color), 3);
            } else if (pixel_size == 4) {
                unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);
                unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
                unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);

                unsigned char color[] = {b, g, r};

                f.write(reinterpret_cast<char*>(color), 4);
            }
        }

        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }

    f.close();

    std::cout << "Image exported successfully" << std::endl;
}

void Image::Filter(const int t, const int k) {
    
}
