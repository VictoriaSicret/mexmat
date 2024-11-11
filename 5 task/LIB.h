#ifndef LIB
#define LIB

#include <type_traits>
#include <exception>
#include <iostream>
#include <string>

namespace INTERFACE {
    template <typename T>
    class InFace {

        protected:
        T* vars;
        size_t num;

        public:
        
        InFace(void);
        InFace(const T&);

        ~InFace(void);

        InFace& operator+= (const InFace&);
        size_t length (void) const;
       
        template <typename V>
        friend std::ostream& operator<< (std::ostream& os, const InFace<V>&);

        T& operator[] (const size_t);
        void start (void);
        void add (void);
        void print (void);
        void action (void);
    };
}

namespace EXCEPT {
    class Except: public std::exception {
		std::string message;
		public:
		Except(const std::string);
		~Except();
		const char* what() const noexcept override;
	};    
}


#endif
