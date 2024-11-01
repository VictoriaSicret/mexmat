#include "interface.h"

using namespace INTERFACE;

int op (const char*, const char*);

int main(void) {
	InFace I;
    List ls1, ls2;
    
    std::cin >> ls1;
    std::cin >> ls2;
    
    I += ls1;
    I += ls2;
    
    I[0].add(&I[1]);
    
    I[0].sort(op);
    
    std::cout << I << std::endl;

    return 0;
}

int op (const char *str1, const char *str2) {
    size_t l1 = strlen(str1), l2 = strlen(str2);
    if (l1 > l2) return 1;
    else if (l1 < l2) return -1;
    size_t i = 0;
    while (i < l1) {
        if (str1[i] < str2[i]) return -1;
        else if (str1[i] > str2[i]) return 1;
        ++i;
    }

    return 0;
}
