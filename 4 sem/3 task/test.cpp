#include "3.h"

int main(void) {
	CintN a; CintN b; std::string val1, val2;
	while (true) {
		try {
			std::cout << "Enter numbers: " << std::endl;
			std::cin >> val1 >> val2;
			a = CintN(val1); b = CintN(val2);
		}
		catch (const ExceptCintN& err) {
			break;
		}
		std::cout << "a = " << a << "\nb = " << b << "\na*b = " << a*b << std::endl;
	}
	
	return 0;
}
