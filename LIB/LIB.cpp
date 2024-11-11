#include "LIB.h"

namespace INTERFACE {
    using namespace EXCEPT; 
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
	
    template <typename T>
    void InFace<T>::add (void) {
        T tmp;
        std::cout <<"\nEnter " << typeid(T).name() << ":" << std::endl;
        std::cin >> tmp;
        *this += tmp; 
    }

    template <typename T>
    void InFace<T>::print (void) {
        for (size_t i = 0; i < num; ++i) {
            std::cout << "\n" << typeid(T).name() << " number " << i << ":\n" << vars[i] << std::endl;
        }
    }

    template <typename T>
    void InFace<T>::action (void) {
        return;    
    } 

    template <typename T>
	void InFace<T>::start(void) {
        int act1 = 0, act2 = 0, way = 0, order = 0; size_t n = 0, m = 0, pos = 0; T list; std::string word;
        while (true) {
            std::cout << "\nChoose action:\n1)Add list\n2)Print\n3)Make action" << std::endl;
            std::cin >> act1;
            if (act1 != 1 && act1 != 2 && act1 != 3) {
                break;
            }
            if (act1 == 1) {
                
                this->add();

            } else if (act1 == 2) {
            
                this->print();
            
            } else {
                this->action();
            }
        }
	}
}

namespace EXCEPT {
	const char* Except::what() const noexcept {
		return message.c_str();
	}

	Except::Except(const std::string text): message(text) { }

	Except::~Except() {	}
    
}
