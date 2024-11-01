#include "interface.h"

namespace INTERFACE {
    InFace::InFace (void) {
        num = 0;
        vars = nullptr;
    }

    InFace::InFace (const List& curr) {
        num = 1;
        vars = new List[num];
        vars[0] = curr;
    }

    InFace::~InFace (void) {
        delete[] vars;
    }

    InFace& InFace::operator+= (const InFace& inface) {
        num += inface.num;
        auto tmp = new List[num];
        for (size_t i = 0; i < num; ++i) {
            tmp[i] = (i < num - inface.num) ? vars[i] : inface.vars[i+inface.num-num];
        }

        delete[] vars;
        vars = tmp;
        return *this;
    }
    
    size_t InFace::length (void) const {
        return num;
    }

    std::ostream& operator<< (std::ostream& os, const InFace& inface) {
        for (size_t i = 0; i < inface.length(); ++i) {
            os << inface.vars[i] << "\n";
        }

        return os;
    }

    List& InFace::operator[] (const size_t k) {
        if (k >= num) throw ListExcept("out of interface");

        return vars[k];
    }
}
