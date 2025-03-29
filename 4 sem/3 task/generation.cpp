#include "3.h"

int main() {
	std::cout << "Enter number of elements and max length of one number: " << std::endl;	
	size_t n, k;
	std::cin >> n >> k;
	
	std::ofstream f;
	f.open("data1.txt"); gen(f, n, k); f.close();
	f.open("data2.txt"); gen(f, n, k); f.close();
	return 0;
}
