#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#define eps 1.0e-15

class Pixel{
	public:
	double r, g, b;

    Pixel(const double& r = 0, const double& g = 0, const double& b = 0);
    ~Pixel();
};

class Image{	
	size_t width;
    size_t height;
    int pixel_size;
    std::vector<Color> pixels;
    
	public:
    
	Image(const size_t& width, const size_t& height, int px_sz);
    ~Image();

	void SetPixel(const Pixel& pixel, const size_t& x, const size_t& y);
    Pixel GetPixel(size_t x, size_t y) const;

    void Read(const char* filename) const;
    void Export(const char* filename) const;
};
