#include "5.h"

namespace INTERFACE {
    using namespace LIST;

    class InFace {
        List* vars;
        size_t num;

        public:
        
        InFace(void);
        InFace(const List&);

        ~InFace(void);

        InFace& operator+= (const InFace&);
        size_t length (void) const;
        friend std::ostream& operator<< (std::ostream& os, const InFace&);

        List& operator[] (const size_t);
    };

    void func(void);
}
