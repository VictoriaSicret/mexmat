#include "lib_BMP.hpp"

#define eps 1.0e-15

	Pixel::Pixel(const double& r, const double& g, const double& b, const double& br) : r(r), g(g), b(b), br(br) {}

	Pixel::~Pixel(){}

	Image::Image(const size_t& width, const size_t& height, const size_t& px_sz) : width(width), height(height), pixel_size(px_sz), pixels(std::vector<Pixel>(width * height)) {}

	Image::~Image() {}

	const Pixel& Image::GetPixel(const size_t& x, const size_t& y) const {return pixels[y*width+x];}

	void Image::SetPixel(const Pixel& pixel, const size_t& x, const size_t& y) {
		pixels[y*width+x].r = pixel.r;
		pixels[y*width+x].g = pixel.g;
		pixels[y*width+x].b = pixel.b;
		pixels[y*width+x].br = pixel.br;
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

		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {
			    if (pixel_size == 3) {
			        unsigned char color[3];
			        f.read(reinterpret_cast<char*>(color), 3);

			        pixels[y * width + x].r = static_cast<double>(color[2]) / 255.0f;
			        pixels[y * width + x].g = static_cast<double>(color[1]) / 255.0f;
			        pixels[y * width + x].b = static_cast<double>(color[0]) / 255.0f;
			    } else if (pixel_size == 4) {
			        unsigned char color[4];
					f.read(reinterpret_cast<char*>(color), 4);

					pixels[y * width + x].r = static_cast<double>(color[2]) / 255.0f;
					pixels[y * width + x].g = static_cast<double>(color[1]) / 255.0f;
					pixels[y * width + x].b = static_cast<double>(color[0]) / 255.0f;
					pixels[y * width + x].br = static_cast<double>(color[3]) / 255.0f;
				}
			}

			f.ignore(paddingAmount);
		}

		f.close();

		std::cout << "File read" << std::endl;
	}

	void Image::Export(const char* filename) const{
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

		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {
				if (pixel_size == 3) {
					unsigned char r = static_cast<unsigned char>(GetPixel(x, y).r * 255.0f);
					unsigned char g = static_cast<unsigned char>(GetPixel(x, y).g * 255.0f);
					unsigned char b = static_cast<unsigned char>(GetPixel(x, y).b * 255.0f);

					unsigned char color[] = {b, g, r};

					f.write(reinterpret_cast<char*>(color), 3);
				} else if (pixel_size == 4) {
					unsigned char r = static_cast<unsigned char>(GetPixel(x, y).r * 255.0f);
					unsigned char g = static_cast<unsigned char>(GetPixel(x, y).g * 255.0f);
					unsigned char b = static_cast<unsigned char>(GetPixel(x, y).b * 255.0f);
					unsigned char br = static_cast<unsigned char>(GetPixel(x, y).br * 255.0f);

					unsigned char color[] = {b, g, r, br};

					f.write(reinterpret_cast<char*>(color), 4);
				}
			}
			f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
		}

		f.close();
	
		std::cout << "Image exported successfully" << std::endl;
	}

	Image Image::Filter(const int k, const int t) const {
		size_t n = this->width;
		size_t m = this->height;

		Image out(n, m, this->pixel_size);

		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				out.SetPixel(this->GetPixel(i, j), i, j);
			}
		}

		std::vector<Pixel> new_pixels((n+2)*(m+2));
		std::vector<Pixel> tmp((n+2)*(m+2));
	
		for (size_t i = 0; i < n+2; ++i) {
		    for (size_t j = 0; j < m+2; ++j) {
		        if (!(i == 0 || i == n+1 || j == 0 || j == m+1))
		            new_pixels[i+j*(n+2)] = GetPixel(i-1, j-1);
		        else
		            new_pixels[i+j*(n+2)] = Pixel();
			}
		}

		for (size_t i = 0; i < n+2; ++i) {
			for (size_t j = 0; j < m+2; ++j) {
			    if (!(i == 0 || i == n+1 || j == 0 || j == m+1))
			        tmp[i+j*(n+2)] = GetPixel(i-1, j-1);
			    else
			        tmp[i+j*(n+2)] = Pixel();
			}
		}

		auto g{[k](const Pixel& x){return 1./(1.+(x.r*x.r+x.g*x.g+x.b*x.b)/(k*k));}};

		double level = 0.;
		double delta_t = 0.25;
		Pixel north{}, south{}, east{}, west{};

		while (level < t) {
		    for (size_t i = 1; i < n+1; ++i) {
		        for (size_t j = 1; j < m+1; ++j) {
		            north = new_pixels[i-1+j*(n+2)]-new_pixels[i+j*(n+2)];
					south = new_pixels[i+1+j*(n+2)]-new_pixels[i+j*(n+2)];
			        east = new_pixels[i+(j+1)*(n+2)]-new_pixels[i+j*(n+2)];
					west = new_pixels[i+(j-1)*(n+2)]-new_pixels[i+j*(n+2)];
                
					tmp[i+j*(n+2)] = new_pixels[i+j*(n+2)] + (north*g(north)+south*g(south)+east*g(east)+west*g(west))*delta_t;
				}
			}

			for (size_t i = 1; i < n+1; ++i) {
				for (size_t j = 1; j < m+1; ++j) {
				    new_pixels[i+j*(n+2)] = tmp[i+j*(n+2)];
				}
			}

			level = level + delta_t;
		}

		for (size_t i = 1; i < n+1; ++i) {
			for (size_t j = 1; j < m+1; ++j) {
				new_pixels[i+j*(n+2)].br = out.GetPixel(i-1, j-1).br;
			    out.SetPixel(new_pixels[i+j*(n+2)], i-1, j-1);
			}
		}

		return out;
	}

	Image Image::FilterParallel(const int k, const int t) const {
		size_t n = this->width;
		size_t m = this->height;

		Image out(n, m, this->pixel_size);
	
		std::vector<std::vector<Pixel>> new_pixels{};
		std::vector<std::vector<Pixel>> tmp{};

		for (size_t i = 0; i < n+2; ++i) {
		    new_pixels.push_back(std::vector<Pixel>{});
		    for (size_t j = 0; j < m+2; ++j) {
		        if (!(i == 0 || i == n+1 || j == 0 || j == m+1))
		            new_pixels[i].push_back(GetPixel(i-1, j-1));
		        else
		            new_pixels[i].push_back(Pixel());
			}
		}

		for (size_t i = 0; i < n+2; ++i) {
			tmp.push_back(std::vector<Pixel>{});
			for (size_t j = 0; j < m+2; ++j) {
			    if (!(i == 0 || i == n+1 || j == 0 || j == m+1))
			        tmp[i].push_back(GetPixel(i-1, j-1));
			    else
			        tmp[i].push_back(Pixel{});
			}
		}

		auto g{[k](const Pixel& x){return 1./(1.+(x.r*x.r+x.g*x.g+x.b*x.b)/(k*k));}};

		double level = 0.;
		double delta_t = 0.25;
		Pixel north{}, south{}, east{}, west{};

		while (level < t) {
			#pragma omp parallel for
			for (size_t i = 1; i < n+1; ++i) {
			    for (size_t j = 1; j < m+1; ++j) {
			        north.r = new_pixels[i-1][j].r-new_pixels[i][j].r;                
			        north.g = new_pixels[i-1][j].g-new_pixels[i][j].g;
			        north.b = new_pixels[i-1][j].b-new_pixels[i][j].b;

			        south.r = new_pixels[i+1][j].r-new_pixels[i][j].r;
			        south.g = new_pixels[i+1][j].g-new_pixels[i][j].g;
			        south.b = new_pixels[i+1][j].b-new_pixels[i][j].b;

			        east.r = new_pixels[i][j+1].r-new_pixels[i][j].r;
			        east.g = new_pixels[i][j+1].g-new_pixels[i][j].g;
			        east.b = new_pixels[i][j+1].b-new_pixels[i][j].b;
                
				    west.r = new_pixels[i][j-1].r-new_pixels[i][j].r;
				    west.g = new_pixels[i][j-1].g-new_pixels[i][j].g;
			        west.b = new_pixels[i][j-1].b-new_pixels[i][j].b;
                
			        tmp[i][j].r = new_pixels[i][j].r + delta_t*(g(north)*north.r+g(south)*south.r+g(east)*east.r+g(west)*west.r);
			        tmp[i][j].g = new_pixels[i][j].g + delta_t*(g(north)*north.g+g(south)*south.g+g(east)*east.g+g(west)*west.g);
			        tmp[i][j].b = new_pixels[i][j].b + delta_t*(g(north)*north.b+g(south)*south.b+g(east)*east.b+g(west)*west.b);
				}
			}
		
			#pragma omp parallel for
			for (size_t i = 1; i < n+1; ++i) {
			    for (size_t j = 1; j < m+1; ++j) {
			        new_pixels[i][j] = tmp[i][j];
				}
			}

			level = level + delta_t;
		}

		for (size_t i = 1; i < n+1; ++i) {
			for (size_t j = 1; j < m+1; ++j) {
			    out.SetPixel(new_pixels[i][j], i-1, j-1);
			}
		}

		return out;
	}

void Image::Brightness(Image& im, const char* name)
{
    Pixel pix;
    double br_1, br_2, bri;
    Image out(im.width, im.height, im.pixel_size);

    for (size_t y = 0; y < im.height; y ++)
    {
        for (size_t x = 0; x < im.width; x ++)
        {
            if (y < height && x < width)
            {
                pix = this -> GetPixel(x, y);
                br_1 = (pix.r + pix.g + pix.b) / 3.0f;

                pix = im.GetPixel(x, y);
                br_2 = (pix.r + pix.g + pix.b) / 3.0f;

                if (br_1 > eps)
                {
                    bri = br_2 / br_1;

                    pix.r = pix.r * bri;
                    pix.g = pix.g * bri;
                    pix.b = pix.b * bri;

                    out.SetPixel(pix, x, y);
                }
            }
            else
            {
                out.SetPixel(im.GetPixel(x, y), x, y);
            }
        }
    }

    out.Export(name);
}
