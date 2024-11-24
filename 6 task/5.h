#ifndef InterFace
#define InterFace

#include "LIST.h"
#include "INTERFACE.h"

namespace InFaceLIST {
    using namespace INTERFACE;
    using namespace LIST;

    class InFaceList: public InFace<List<std::string> > {
        public:
        bool action(void) override;
    };
}

#endif
