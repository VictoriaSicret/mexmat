#include "3.h"
int main(){
	std::srand(std::time({}));
	
	std::vector<CintN*> v1, v2, vv1, vv2; 
	std::vector<CintN1> res1;     std::vector<CintN2> res2;
	std::vector<CintN1> multRes1; std::vector<CintN2> multRes2; 

	std::vector<CFabric*> fabric;
	fabric.push_back(new CFabric1);
	fabric.push_back(new CFabric2);

//	std::cout << "Enter number of elements and max length of one number: " << std::endl;	
//	size_t n, k;
//	std::cin >> n >> k;
	
	std::ofstream f;
//	f.open("data1.txt"); gen(f, n, k); f.close();
//	f.open("data2.txt"); gen(f, n, k); f.close();
    
	std::ifstream in1("data1.txt");
    std::ifstream in2("data2.txt");
	
	try {
		if (Input(0, in1, in2, v1, v2, fabric) == -1) throw ExceptCintN("not same number");
		in1.close(); in2.close();
		in1.open("data1.txt"); in2.open("data2.txt");
		if (Input(1, in1, in2, vv1, vv2, fabric) == -1) throw ExceptCintN("not same number");
	} catch (const ExceptCintN& err) {
		std::cout << err.what() << std::endl;
		in1.close(); in2.close(); return -1;
	}

	in1.close(); in2.close();
	std::cout << "input success" << std::endl;
	
	for (size_t i = 0; i < v1.size(); ++i) {res1.push_back(0); res2.push_back(0); multRes1.push_back(0); multRes2.push_back(0);}

	int timer1 = -clock();
	for (size_t i = 0; i < v1.size(); ++i) res1[i] = *v1[i]+*v2[i];
	timer1 += clock();

	int timer2 = -clock();
	#pragma omp parallel for
    for (size_t i = 0; i < v1.size(); ++i) res2[i] = *v1[i]+*v2[i];
	timer2 += clock();
	
	std::cout << "addition success" << std::endl;
	
	int timerM1 = -clock();
	for (size_t i = 0; i < v1.size(); ++i) multRes1[i] = (*v1[i])*(*v2[i]);
	timerM1 += clock();

	int timerM2 = -clock();
	for (size_t i = 0; i < v1.size(); ++i) multRes2[i] = (*vv1[i])*(*vv2[i]);
	timerM2 += clock();

	std::cout << "multiplication success" << std::endl;
	//for (size_t i = 0; i < result.size()/2; ++i) {v1[i]->Show();}
	//f.open("res.txt", std::ios::app); f << "\n\n"; f.close();
	//for (size_t i = 0; i < result.size()/2; ++i) {v2[i]->Show();}
	//f.open("res.txt", std::ios::app); f << "\n\n\n"; f.close();

	//for (size_t i = 0; i < result.size()/2; ++i) {result[i]->Show();}
	//for (size_t i = result.size()/2; i < result.size(); ++i) {result[i]->Show();}
	f.open("res.txt");
   	f << "time for addition: " << static_cast<double>(timer1)/CLOCKS_PER_SEC << "\n"; 
	f << "time for addition with parallel: " << static_cast<double>(timer2)/CLOCKS_PER_SEC << "\n";
	f << "time for multiplication: " << static_cast<double>(timerM1)/CLOCKS_PER_SEC << "\n";
	f << "time for multiplication with parallel: " << static_cast<double>(timerM2)/CLOCKS_PER_SEC << "\n";

	bool flag = true;
	for (size_t i = 0; i < v1.size(); ++i) {if (res1[i] != res2[i] || multRes1[i] != multRes1[i]) flag = false;}
	f << ((flag) ? "Correct" : "Incorrect"); f.close();
	if (!flag) std::cout << "\nERROR: Not same answers." << std::endl;

    for (size_t i = 0; i < v1.size(); ++i) {delete v1[i]; delete v2[i]; delete vv1[i]; delete vv2[i];}

	for (size_t i = 0; i < fabric.size(); ++i) delete fabric[i];
    return 0;
}
