#include<iostream>
#include "5.h"

using namespace LIST;

int main(void) {
	List ls1, ls2;
    ls1.pushBack("hello");
    ls2.pushBack("world");
    ls2.pushHead("WORLD");
    ls1.pushHead("HELLO");
    
    ls1.add(&ls2);
    
    for (auto iter = ls1.begin(); iter != ls1.end(); ++iter) {
        char* tmp = *iter;
        std::cout << tmp << std::endl;
        delete[] tmp;
    }

    return 0;
}
