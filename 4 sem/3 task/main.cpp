#include "3.h"
int main(){
	std::srand(std::time({}));
	std::vector<CintN*> v1, v2, result;
	std::vector<CFabric*> fabric;
	fabric.push_back(new CFabric1);
	fabric.push_back(new CFabric2);
	std::cout << "Enter number of elements and max length of one number: " << std::endl;	
	size_t n, k;
	std::cin >> n >> k;
	std::ofstream f;
	f.open("data1.txt"); gen(f, n, k); f.close();
	f.open("data2.txt"); gen(f, n, k); f.close();
    std::ifstream in1("data1.txt");
    std::ifstream in2("data2.txt");
	try {
		Input(in1, in2, v1, v2, fabric);
	} catch (const ExceptCintN& err) {
		std::cout << err.what() << std::endl;
		in1.close(); in2.close(); return -1;
	}
	std::cout << "input success" << std::endl;
	int timer1 = -clock();
    for (size_t i = 0; i < v1.size()/2; ++i) {
		//Add time check
		CintN1* tmp = new CintN1(*v1[i]+*v2[i]);
		result.push_back(tmp);
	}
	timer1 += clock();

	int timer2 = -clock();
    for (size_t i = v1.size()/2; i < v1.size(); ++i) {
		//Add time check
		CintN2* tmp = new CintN2(*v1[i]+*v2[i]);
		result.push_back(tmp);
	}
	timer2 += clock();

	f.open("res.txt"); f.close();
	std::cout << "addition success" << std::endl;
	//for (size_t i = 0; i < result.size()/2; ++i) {v1[i]->Show();}
	//f.open("res.txt", std::ios::app); f << "\n\n"; f.close();
	//for (size_t i = 0; i < result.size()/2; ++i) {v2[i]->Show();}
	//f.open("res.txt", std::ios::app); f << "\n\n\n"; f.close();

	//for (size_t i = 0; i < result.size()/2; ++i) {result[i]->Show();}
	//for (size_t i = result.size()/2; i < result.size(); ++i) {result[i]->Show();}
	f.open("res.txt", std::ios::app); f << "\n" << "time: " << static_cast<double>(timer1)/CLOCKS_PER_SEC << "\n\n"; f.close();
	f.open("res.txt", std::ios::app); f << "\n" << "time with parallel: " << static_cast<double>(timer2)/CLOCKS_PER_SEC << "\n\n"; f.close();

	bool flag = true;
	for (size_t i = 0; i < result.size()/2; ++i) {if (*result[i] != *result[i+result.size()/2]) flag = false;}
	f.open("res.txt", std::ios::app); f << ((flag) ? "Correct" : "Incorrect"); f.close();
	if (!flag) std::cout << "\nERROR: Not same answers." << std::endl;

    for (size_t i = 0; i < v1.size(); ++i) {delete v1[i]; delete v2[i]; delete result[i];}

	for (size_t i = 0; i < fabric.size(); ++i) delete fabric[i];
    return 0;
}
