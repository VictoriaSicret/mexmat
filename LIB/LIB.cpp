#include "LIB.h"

namespace INTERFACE {
    template <typename T> 
    InFace<T>::InFace (void) {
        num = 0;
        vars = nullptr;
    }

    template <typename T> 
    InFace<T>::InFace (const T& curr) {
        num = 1;
        vars = new T[num];
        vars[0] = curr;
    }

    template <typename T> 
    InFace<T>::~InFace (void) {
        delete[] vars;
    }

    template <typename T> 
    InFace<T>& InFace<T>::operator+= (const InFace& inface) {
        num += inface.num;
        auto tmp = new T[num];
        for (size_t i = 0; i < num; ++i) {
            tmp[i] = (i < num - inface.num) ? vars[i] : inface.vars[i+inface.num-num];
        }

        delete[] vars;
        vars = tmp;
        return *this;
    }
    
    template <typename T>
    size_t InFace<T>::length (void) const {
        return num;
    }
    
    template <typename T>
    std::ostream& operator<< (std::ostream& os, const InFace<T>& inface) {
        for (size_t i = 0; i < inface.length(); ++i) {
            os << inface.vars[i] << "\n";
        }

        return os;
    }

    template <typename T>
    T& InFace<T>::operator[] (const size_t k) {
        if (k >= num) throw Except("out of interface");

        return vars[k];
    }

}

namespace EXCEPT {
	const char* Except::what() const noexcept {
		return message.c_str();
	}

	ListExcept::ListExcept(const std::string text): message(text) { }

	ListExcept::~ListExcept() {	}
    
}
