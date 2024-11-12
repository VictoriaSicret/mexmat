#ifndef InterFace
#define InterFace

#include "5.h"

namespace InFaceLIST {
    using namespace INTERFACE;
    using namespace LIST;

    class InFaceList: public InFace<List> {
        public:
        bool action(void) override;
    };
}

#endif
