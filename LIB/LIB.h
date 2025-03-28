#ifndef LIB_FOR_ALL
#define LIB_FOR_ALL

#include <type_traits>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>

namespace EXCEPT {
    class Except: public std::exception {
		std::string message;
		public:
		Except(const std::string text): message(text) { }
		~Except() {	}
		const char* what() const noexcept override {
			return message.c_str();
		}
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

		virtual ~InFace (void) {
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
	
		bool add (void) {
            int way = 0, n = 0;
            std::cout <<"\nChoose way for input:\n1)Console\n2)File\n3)Generate" << std::endl;
			std::cin >> way;
            if (way != 1 && way != 2 && way != 3) return true;
            T tmp;
            if (way == 1) {
	    		std::cout <<"\nEnter " << T::name() << ":" << std::endl;
			    std::cin >> tmp;
            } else if (way == 2) {
                std::string filename;
                std::cout << "\nEnter filename:" << std::endl;
                std::cin >> filename;
                std::ifstream file; file.open(filename, std::ios::in);
                if (file.is_open()) {
                    file >> tmp;
                } else {
                    return true;
                }
            } else {
                srand((int)time(NULL));
                std::cout <<"\nEnter number of fields:" << std::endl;
                std::cin >> n;
                if (n < 0) return true;
                tmp.generate(n);
            }

            *this += tmp;
            return false; 
		}
    
		bool print (void) {
            int way = 0;
            std::cout <<"\nChoose way for data:\n1)Console\n2)File" << std::endl;
            std::cin >> way;
            if (way != 1 && way != 2) return true;
            if (way == 1) {
        	    for (size_t i = 0; i < num; ++i) {
			        std::cout << "\n" << T::name() << " number " << i << ":\n" << vars[i] << std::endl;
			    }
            } else {
                std::string filename;
                std::cout << "\nEnter filename:" << std::endl;
                std::cin >> filename;
                std::ofstream file; file.open(filename, std::ios::out);
                if (file.is_open()) {
        	        for (size_t i = 0; i < num; ++i) {
			            file << "\n" << T::name() << " number " << i << ":\n" << vars[i] << "\n";
			        }
                } else {
                    return true;
                }
            }

            return false;
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
	                
	                if(this->add()) break;
	
	            } else if (act == 2) {
            
	                if (this->print()) break;
	            
	            } else {
	                if (this->action()) break;
	            }
	        }
		}
    };
}

namespace CMP {
	int cmplen (const std::string str1, const std::string str2);
	int cmp (const std::string str1, const std::string str2);


    int cmplen (const std::string str1, const std::string str2) {
        if (str1.length() < str2.length()) return -1;
        if (str1.length() > str2.length()) return 1;
        return 0;
    }

	int cmp (const std::string str1, const std::string str2) {
        if (cmplen(str1, str2) != 0) return cmplen(str1, str2);
        if (str1 > str2) return 1;
        if (str1 < str2) return -1;

        return 0;
    }
    
}

namespace LIST {
    using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using Diff = std::chrono::milliseconds;

    using namespace EXCEPT;
	template <typename T>
	class List;

    template <typename T>
    T generateType (void);

	template <typename T>
	std::ostream& operator<< (std::ostream&, const List<T>&);
    template <typename T>
	std::istream& operator>> (std::istream&, List<T>&);
	
	template <typename T>
	class List {
		template <typename K> 
        friend class ListInFace;
        
		template <typename V>
		class Node {
            public:
            
            V mes;
            Node* last;
            Node* next;
                       
            Node(const V text): mes(text) {
        		next = nullptr;
        		last = nullptr; 
    		}		

			~Node() {
    		    last = nullptr;
    		    next = nullptr;
    		}
            
			V val(void) const {
     		   return mes;
  		  	}
        };

        template <typename V>
        class iterator {
            public:

            const List<V> *lst;
			Node<V>* pos;
            size_t index;

    		iterator (const List<V>* list = nullptr, Node<V>* node = nullptr, const size_t ind = 0): index(ind) {
    	    	lst = list;
        		pos = node;
    		}
    		
            ~iterator(void) {
        		lst = nullptr;
        		pos = nullptr;
    		}

            iterator& operator++(void) {
        		if (pos == nullptr) return *this;
        		pos = pos->next;
        		index++;
        		return *this;
    		}
    	    iterator operator++(int) {
		        if (pos == nullptr) return *this;
    		    iterator old = *this;
    		    ++(*this);
    		    return old;
    		}

    		iterator& operator--(void) {
    		    if (pos == nullptr) return *this;
    		    pos = pos->last;
    		    index--;
    		    return *this;
    		}

    		iterator operator--(int) {
    		    if (pos == nullptr) return *this;
    		    iterator old = *this;
    		    --(*this);
    		    return old;
    		}
    
    	    iterator operator+(size_t k) {
    		    if (pos == nullptr) return *this;
    		    auto tmp = pos;
    		    for (size_t i = 0; i < k; ++i) {
    		        if (tmp != nullptr) tmp = tmp->next;
					else return lst->end();
        		}
    		    return iterator(lst, tmp, index+k);
    		}
    		
    		bool operator== (const iterator& i) const {
    		    return (lst == i.lst && index == i.index) ? true : false;
    		}

    		bool operator!= (const iterator& i) const {
    		    return !(*this == i);
    		}
			
		    V& operator* (void) {
    		    return pos->mes;
    		}

    		size_t Index (void) {
    		    return index;
    		}
        };
        
		Node<T>* head;
		Node<T>* back;
        size_t size;
		
		public:

		List(void){
			head = nullptr;
        	back = nullptr;
        	size = 0;
		}
		
		~List() {
			while (size != 0) {
    	        if (size == 1) {
    	            delete back;
    	            back = nullptr; head = nullptr;
    	            size = 0;
    	            continue;
    	        }
				back = back->last;
    	        back->next->last = nullptr;
    	        delete back->next;
    	        back->next = nullptr;
    	        size--;
			}
		}

    	List(const List& ls) {
        	size = 0;
        	for (auto iter = ls.begin(); iter != ls.end(); ++iter) {
        	    if (size == 0) {
        	        back = new Node<T>(*iter);
        	        head = back;
        	        size++;
        	        continue;
        	    }
        	    back->next = new Node<T>(*iter);
        	    back->next->last = back;
        	    back = back->next;
        	    size++;
        	}
    	}
    	
        List(List&& move) {
       		size = move.size;
        	move.size = 0;
        	head = move.head;
        	move.head = nullptr;
        	back = move.back;
        	move.back = nullptr;
    	}
    	
        List& operator= (const List& ls) {
        	this->clear();
        	if (ls.empty()) return *this;
        	for (auto iter = ls.begin(); iter != ls.end(); ++iter) {
        	    this->pushBack(*iter);
        	}

        	return *this;
    	}
    	
        List& operator= (List&& move) {
    	    this->clear();

    	    size = move.size;
    	    move.size = 0;
    	    head = move.head;
    	    move.head = nullptr;
    	    back = move.back;
    	    move.back = nullptr;
	
   		    return *this;
    	}

		void pushBack(const T text) {
    	    if (size == 0) {
   		        back = new Node<T>(text);
    	        head = back;
        	    size = 1;
        	    return;
        	}
			back->next = new Node<T>(text);
			back->next->last = back;
			back = back->next;
        	size++;
		}
		
        void popBack(void) {
        	if (size == 0) {
        	    return;
        	}
        	if (size == 1) {
        	    delete back;
        	    back = head = nullptr;
        	} else {
        	    back = back->last;
        	    delete back->next;
        	    back->next = nullptr;
        	}
        	size--;
    	}

        void pushHead(const T text) {
        	if (size == 0) {
        	    head = new Node<T>(text);
        	    back = head;
        	    size = 1;
        	    return;
        	}
        	head->last = new Node<T>(text);
        	head->last->next = head;
        	head = head->last;
        	size++;
    	}
    	
        void popHead(void) {
        	if (size == 0) return;
        	if (size == 1) {
        	    delete back;
        	    back = head = nullptr;
        	} else {
        	    head = head->next;
        	    delete head->last;
        	    head->last = nullptr;
        	}
        	size--;
    	}

        void pushIn(const size_t k, const T text) {
        	if (k > size) throw Except("out of range");
        	if (k == 0) {
        	    this->pushHead(text);
        	    return;
        	}
        	if (k == size) {
        	    this->pushBack(text);
        	    return;
        	}
        	auto iter = this->begin();
        	for (size_t i = 0; i < k; ++i) ++iter;
        	auto block = new Node<T>(text);

        	iter.pos->last->next = block;
        	block->next = iter.pos;
        	block->last = iter.pos->last;
        	iter.pos->last = block;
        	size++;
    	}
		 
        void pushIn (iterator<T> iter, const T text) {
            if (iter.Index() == 0) {
                this->pushHead(text);
                return;
            }
            if (iter.Index() == size) {
                this->pushBack(text);
                return;
            }
            auto block = new Node<T>(text);
            iter.pos->last->next = block;
            block->next = iter.pos;
            block->last = iter.pos->last;
            iter.pos->last = block;
            size++;
        }
        
        void popIn(const size_t k) {
        	if (k > size) throw Except("out of range");
        	if (k == 0) {
        	    this->popHead();
        	    return;
        	}
        	if (k == size) {
        	    this->popBack();
        	    return;
        	}

        	auto iter = this->begin() + k;
        	iter.pos->last->next = iter.pos->next;
        	iter.pos->next->last = iter.pos->last;
        	delete iter.pos;
        	size--;
    	}     

        void popIn(iterator<T> iter) {
            if (iter.Index() == 0) {
                this->popHead();
                return;
            }
            if (iter.Index() == size) {
                this->popBack();
                return;
            }

            iter.pos->last->next = iter.pos->next;
            iter.pos->next->last = iter.pos->last;
            delete iter.pos;
            size--;
        }
        
        bool empty(void) const {
        	return size == 0;
   		}
        size_t length(void) const {
        	return size;
    	}
        
    	List add(const List* curr) {
    	    List res = *this;
    	    for (auto iter = curr->begin(); iter != curr->end(); ++iter) {
    	        res.back->next = new Node<T>(*iter);

    	        res.back->next->last = res.back;
    	        res.back = res.back->next;
    	        res.size++;
    	    }
    	    return res;
    	}
    	
        void clear (void) {
    	    while (size > 0) {
    	        this->popBack();
    	    }
    	}
	    
   		List sort(int (*op)(const T, const T)) {

            Time t1 = std::chrono::high_resolution_clock::now();

        	List tmp; bool flag = true;
        	for (auto iter = this->begin(); iter != this->end(); ++iter) {
        	    if (tmp.empty()) {
        	        tmp.pushBack(*iter);
        	        continue;
        	    }
	
    	        for (auto it = tmp.begin(); it != tmp.end(); ++it) {
    	            if (op(*iter, *it) == 1) continue;
    	            else {
    	                tmp.pushIn(it, *iter);
    	                flag = false;
    	                break;
        	        }
        	    }
        	    if (flag) tmp.pushBack(*iter); 
        	    else flag = true;

        	}
            Time t2 = std::chrono::high_resolution_clock::now();
            Diff diff = std::chrono::duration_cast<Diff>(t2 - t1);
            std::cout << "\nTime: "<< diff.count() << " ms" << std::endl;
            
        	return tmp;
    	}
        
        void swap (iterator<T> i1, iterator<T> i2) {
    	    List<T> ls;
        
    	    for (auto iter = i1.lst->begin(); iter != i1.lst->end(); ++iter) {
    	        if (iter == i1) {
    	            ls.pushBack(*i2);
    	        }
    	        else if (iter == i2) {
    	            ls.pushBack(*i1);
    	        }
    	        else {
    	            ls.pushBack(*iter);
    	        }
    	    }
    	    *this = ls;
    	}

    		iterator<T> begin(void)  const{
    	    return iterator<T>(this, head, 0);
    	}

    	iterator<T> end(void) const {
    	    return iterator<T>(this, back->next, size);
    	}

		static std::string name (void) {
			return std::string("List");
		}

		void generate(size_t num) {
            this->clear();

            for (size_t i = 0; i < num; ++i) {
                this->pushBack(generateType<T>());
            }
        }
    };
    
    template <typename K>
    class ListInFace;

	template <typename T>
    std::ostream& operator<< (std::ostream& os, const List<T>& list) {
        if (list.empty()) return os << "\n";
        for (auto iter = list.begin(); iter != list.end(); ++iter) {
            os << *iter << "\n";
        }

        return os;
    }
	
	template <typename T>
    std::istream& operator>> (std::istream& is, List<T>& list) {
        list.clear();
        size_t num = 0;
        is >> num;
        
        for (size_t i = 0; i < num; ++i) {
            T tmp;
            is >> tmp;
            list.pushBack(tmp);
        }

        return is;
    }

    template <typename T>
    std::ostream& operator<< (std::ostream&, const ListInFace<T>&);

    template <typename T>
    class ListInFace {
        List<T>* list;
        typename List<T>::template iterator<T> pos;

        public:

        ListInFace(List<T>* ls) {
            list = ls;
            pos = ls->begin();
        }

        ~ListInFace(void) {
            list = nullptr;
        }

        void begin(void) {
            pos = list->begin();
        }

        void end(void) {
            pos = list->begin();
            pos = pos + (list->length()-1);
        }
        
        template <typename K>
        friend std::ostream& operator<< (std::ostream& os, const ListInFace<K>& inface);

        void operator++ (void) {
            if (pos.pos->next == nullptr) throw Except("go out of range");
            ++pos;
        }

        void operator-- (void) {
            if (pos.pos->last == nullptr) throw Except("go out of range");
            --pos;
        }

        size_t Index(void) {
            return pos.Index();
        }

        T& operator*(void) {
            return *pos;
        }

        void go(void) {
            size_t act = 0, way = 0, i = 0;
            while (true) {
                std::cout << "\nChoose:\n1)Move pointer\n2)Change by pointer\n3)get index\n4)Print list" << std::endl;
                std::cin >> act;
                if (act != 1 && act != 2 && act != 3 && act != 4) break;

                if (act == 1) {
                    std::cout <<"\nmove to:\n1)begin\n2)end\n3)next\n4)previos\n5)enter index" << std::endl;
                    std::cin >> way;
                    if (way != 1 && way != 2 && way != 3 && way != 4 && way != 5) break;
                    
                    if (way == 1) this->begin();
                    else if (way == 2) this->end();
                    else if (way == 3) ++(*this);
                    else if (way == 4) --(*this);
                    else {
                        std::cout <<"\nEnter index:" << std::endl;
                        std::cin >> i;
                        if (i >= list->length()) break;
                        this->begin();
                        for (size_t k = 0; k < i; ++k) ++(*this);
                    }
                } else if (act == 2) {
                    std::cout << "\nOld value: " << *(*this)<< std::endl;
                    std::cout <<"\nEnter new value:" << std::endl;
                    std::cin >> *(*this);
                } else if (act == 3) {
                    std::cout << "\nIndex = " <<this->Index() << std::endl;
                } else {
                    std::cout << *this << std::endl;
                }

            }
        }

    };
        
	template <typename T>
    std::ostream& operator<< (std::ostream& os, const ListInFace<T>& inface) {
        if (inface.list->empty()) return os << "\n";
        for (auto iter = inface.list->begin(); iter != inface.list->end(); ++iter) {
            if (iter == inface.pos) {
                os << *iter <<"*\n";
            } else {
                os << *iter <<"\n";
            }
        }
        return os;
    }

}

namespace COMPLEX{ 

	constexpr double eps = 1e-12;
	
	class Complex {
		double x, y;
	
		public:
		Complex(): x(0.), y(0.) {}
		
		Complex(double a, double b = 0): x(a), y(b) {}
	
		Complex(const Complex& z): x(z.x), y(z.y) {}
		
		Complex(Complex&& mv) {
			x = mv.x;
			y = mv.y;
			mv.x = mv.y = 0;
		}

		~Complex() {};
		
		double real(void) const {
			return x;
		}

		double imag(void) const {
			return y;
		}
			
		Complex& operator= (const Complex& z) {
			x = z.x; y = z.y;
			return *this;
		}

		Complex& operator= (Complex&& mv) {
			x = mv.x; y = mv.y;
			mv.x = mv.y = 0;
			return *this;
		}
		
		friend Complex operator+ (const Complex& z1, const Complex& z2);
		friend Complex operator- (const Complex& z1, const Complex& z2);
		friend Complex operator* (const Complex& z1, const Complex& z2);
		friend Complex operator/ (const Complex& z1, const Complex& z2);
		friend Complex operator- (const Complex& z);
		friend Complex operator+ (const Complex& z);

		friend bool operator== (const Complex& z1, const Complex& z2);
		friend bool operator!= (const Complex& z1, const Complex& z2);
		friend bool operator< (const Complex& z1, const Complex& z2);	
		friend bool operator<= (const Complex& z1, const Complex& z2);
		friend bool operator> (const Complex& z1, const Complex& z2);
		friend bool operator>= (const Complex& z1, const Complex& z2);

		friend std::string print(const Complex& z);
		friend std::ostream& operator<< (std::ostream& os, const Complex& z);
		friend std::istream& operator>> (std::istream& is, Complex& z);

		friend Complex rev(const Complex& z);
		friend Complex conj (const Complex& z);
		friend double mod(const Complex& z);
		friend double arg(const Complex& z);
		friend Complex powCI(const Complex& base, const int& exp);

		Complex& operator+= (const Complex& z) {
			*this = *this + z;
			return *this;
		}

		Complex& operator-= (const Complex& z) {
			*this = *this - z;
			return *this;
		}
	
		Complex& operator*= (const Complex& z) {
			*this = (*this)*z;
			return *this;
		}

		Complex& operator/= (const Complex& z) {
			*this = *this/z;
			return *this;
		}
	};
	
	
	Complex operator+ (const Complex& z1, const Complex& z2) {
		return Complex(z1.real()+z2.real(), z1.imag() + z2.imag()); 
	}

	Complex operator- (const Complex& z1, const Complex& z2) {
		return Complex(z1.real()-z2.real(), z1.imag() - z2.imag());
	}
	
	Complex operator* (const Complex& z1, const Complex& z2) {
		return Complex(z1.real()*z2.real()-z1.imag()*z2.imag(), z1.real()*z2.imag()+z1.imag()*z2.real());
	}

	Complex operator/ (const Complex& z1, const Complex& z2) {
		return z1*rev(z2);			
	}

	Complex operator- (const Complex& z) {
		return Complex(-z.real(), -z.imag());
	}

	Complex operator+ (const Complex& z) {
		return Complex(z.real(), z.imag());
	}

	bool operator== (const Complex& z1, const Complex& z2) {
		return fabs(z1.real()-z2.real()) < eps && fabs(z1.imag()-z2.imag()) < eps;
	}
	
	bool operator!= (const Complex& z1, const Complex& z2) {
		return !(z1 == z2);
	}
	
	bool operator< (const Complex& z1, const Complex& z2) {
		return (z1.real() < z2.real() && z1.imag() < z2.imag());
	}

        bool operator<= (const Complex& z1, const Complex& z2) {
		return z1 == z2 || z1 < z2;
	}

        bool operator> (const Complex& z1, const Complex& z2) {
		return !(z1 <= z2);
	}

        bool operator>= (const Complex& z1, const Complex& z2) {
		return !(z1 < z2);
	}

	std::string print(const Complex& z) {
		std::string str;
		str += std::to_string(z.real());
		if (fabs(z.imag()) > eps) {
			str += "+i*("+std::to_string(z.imag()) + ")";
		}
		return str;
	}

	std::ostream& operator<< (std::ostream& os, const Complex& z) {
		return os <<"(" << print(z) << ")";
	}

	std::istream& operator>> (std::istream& is, Complex& z) {
		is >> z.x >> z.y;
		return is;
	}

	 Complex rev(const Complex& z) {
                 if (mod(z) < eps || mod(z)*mod(z) < eps) {
                         exit(-1);
                 }
                 return Complex(z.real()/(mod(z)*mod(z)), -z.imag()/(mod(z)*mod(z)));
         }

         Complex conj (const Complex& z) {
                 return Complex(z.real(), -z.imag());
         }

         double mod(const Complex& z) {
                 return sqrt(z.real()*z.real()+z.imag()*z.imag());
         }

         double arg(const Complex& z) {
                 if (fabs(z.real()) < eps) {
                         return M_PI/2;
                 }
                 return atan2(z.imag(), z.real()) ;
         }

	Complex powCI(const Complex& base, const int& exp) {
		Complex a(base), y(1); int b(exp);

		while (b > 0) {
			if (b%2 == 0) {
				b /= 2;
				a *= a;
			} else {
				b--;
				y *= a;
			}
		}
		return y;
	}
}

#endif
