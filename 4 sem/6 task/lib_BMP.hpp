#ifndef BMPImage
#define BMPImage

#include <vector>
#include <fstream>
#include <iostream>
#include <omp.h>

	class Pixel{
		public:
		double r, g, b, br;

	    Pixel(const double& r = 0, const double& g = 0, const double& b = 0, const double& br = 1.);
	    ~Pixel(void);
		Pixel& operator= (const Pixel& pxl) {
			r = pxl.r; g = pxl.g; b = pxl.b; br = pxl.br; return *this;	
		}

		Pixel operator+ (const Pixel& p) const {
			return Pixel(r+p.r, g+p.g, b+p.b, 1.);
		}

		Pixel operator- (const Pixel& p) const {
			return Pixel(r-p.r, g-p.g, b-p.b, 1.);
		}

		Pixel operator* (const double& v) const {
			return Pixel(r*v, g*v, b*v, 1.);
		}

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
	    const Pixel& GetPixel(const size_t& x, const size_t& y) const;

	    void Read(const char* filename);
	    void Export(const char* filename) const;
		Image Filter(const int t, const int k) const;
		Image FilterParallel(const int t, const int k) const;
		void Brightness(Image& im, const char* name);
	};

#endif
