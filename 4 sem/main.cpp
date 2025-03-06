#include "1.h"

int main(void) {
    std::vector<CintN*> v;
    std::ifstream in("data.txt");
    Input(in, v);

    std::cout << "File input test\n" << std::endl;

    for (size_t i = 0; i < v.size(); ++i) v[i]->Show();

    std::cout << "\nDestructor test" << std::endl;

    for (size_t i = 0; i < v.size(); ++i) delete v[i];

    return 0;
}
