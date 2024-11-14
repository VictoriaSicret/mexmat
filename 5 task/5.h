#ifndef InterFace
#define InterFace

#include "LIB.h"

namespace InFaceLIST {
    using namespace INTERFACE;
    using namespace LIST;
    
    class InFaceList: public InFace<List<std::string> > {
        public:
        bool action(void) override;
    };
}

#endif
