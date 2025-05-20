#ifndef BMPImage
#define BMPImage

#include <vector>
#include <fstream>
#include <iostream>
#include <omp.h>

	class Pixel{
		public:
		double r, g, b, br;

	    Pixel(const double& r = 0, const double& g = 0, const double& b = 0, const double& br = 0);
	    ~Pixel(void);
	};

	class Image{	
		size_t width;
	    size_t height;
	    size_t pixel_size;
	    std::vector<Pixel> pixels;
	    
		public:
	    
		Image(const size_t& width, const size_t& height, const size_t& px_sz);
		~Image(void);

		void SetPixel(const Pixel& pixel, const size_t& x, const size_t& y);
	    Pixel GetPixel(const size_t& x, const size_t& y) const;

	    void Read(const char* filename);
	    void Export(const char* filename) const;
		Image Filter(const int t, const int k) const;
		Image FilterParallel(const int t, const int k) const;
	};

#endif
