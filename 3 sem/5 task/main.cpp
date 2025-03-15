#include "5.h"

using namespace InFaceLIST;
int main(void) {
    InFaceList interface;
    try{
        interface.start();
    } catch (Except& excp){
        std::cout << excp.what()<< std::endl;
        return -1;
    }
    return 0;
}
