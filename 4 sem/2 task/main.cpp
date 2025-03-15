#include "2.h"

int main(void) {
    std::vector<CintN*> v;
	std::vector<CFabric*> fabric;
	fabric.push_back(new CFabric1);
	fabric.push_back(new CFabric2);

    std::ifstream in("data.txt");
    Input(in, v, fabric);
    std::cout << "File input test\n" << std::endl;

    for (size_t i = 0; i < v.size(); ++i) v[i]->Show();

    std::cout << "\nDestructor test" << std::endl;

    for (size_t i = 0; i < v.size(); ++i) delete v[i];

    return 0;
}
