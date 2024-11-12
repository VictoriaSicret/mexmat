#ifndef LIB_FOR_ALL
#define LIB_FOR_ALL

#include <type_traits>
#include <exception>
#include <iostream>
#include <string>

namespace EXCEPT {
    class Except: public std::exception {
		std::string message;
		public:
		Except(const std::string);
		~Except();
		const char* what() const noexcept override;
	};    
}

namespace INTERFACE {
	using namespace EXCEPT;
	
	template <typename T>
    class InFace {

        protected:
        T* vars;
        size_t num;

        public:
		
		InFace (void) {
			num = 0;
			vars = nullptr;
		}

		InFace (const T& curr) {
			num = 1;
			vars = new T[num];
			vars[0] = curr;
		}

		~InFace (void) {
			delete[] vars;
		}

		InFace<T>& operator+= (const InFace<T>& inface) {
			num += inface.num;
			auto tmp = new T[num];
			for (size_t i = 0; i < num; ++i) {
			    tmp[i] = (i < num - inface.num) ? vars[i] : inface.vars[i+inface.num-num];
			}

			delete[] vars;
			vars = tmp;
			return *this;
		}
		
		size_t length (void) const {
			return num;
		}
    
		friend std::ostream& operator<< (std::ostream& os, const InFace<T>& inface) {
			for (size_t i = 0; i < inface.length(); ++i) {
				os << inface.vars[i] << "\n";
			}

			return os;
		}

		T& operator[] (const size_t k) {
			if (k >= num) throw Except("out of interface");

			return vars[k];
		}
	
		void add (void) {
			T tmp;
			std::cout <<"\nEnter " << T::name() << ":" << std::endl;
			std::cin >> tmp;
			*this += tmp; 
		}
    
		void print (void) {
			for (size_t i = 0; i < num; ++i) {
			    std::cout << "\n" << T::name() << " number " << i << ":\n" << vars[i] << std::endl;
			}
		}

		virtual bool action (void) {
			std::cout <<"Not ready yet." << std::endl;
			return false;
		} 

		void start(void) {
		    int act = 0;
		    while (true) {
		        std::cout << "\nChoose action:\n1)Add list\n2)Print\n3)Make action" << std::endl;
		        std::cin >> act;
		        if (act != 1 && act != 2 && act != 3) {
		            break;
		        }
	            if (act == 1) {
	                
	                this->add();
	
	            } else if (act == 2) {
            
	                this->print();
	            
	            } else {
	                if (this->action()) break;
	            }
	        }
		}
    };
}

#endif
