#include <ctime>
#include "lib_BMP.hpp"

int main(void){
	Image img(0, 0, 0);
	img.Read("test.bmp");
	
	int timer1 = -clock();
	auto img_new = img.Filter(15, 15);
	timer1 += clock();

	int timer2 = -clock();
	auto img_newParallel = img.Filter(15, 15);
	timer2 += clock();
	
	std::cout << "time for filtration: " << static_cast<double>(timer1)/CLOCKS_PER_SEC << "\n"; 
	std::cout << "time for filtration with parallel: " << static_cast<double>(timer2)/CLOCKS_PER_SEC << "\n";
	
	img_new.Export("test_clear.bmp");
	img_newParallel.Export("test_clear_parallel.bmp");
	return 0;
}
