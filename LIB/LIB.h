#ifndef LIB
#define LIB

namespace INTERFACE {
    template <typename T>
    class InFace {
        T* vars;
        size_t num;

        public:
        
        InFace(void);
        InFace(const T&);

        ~InFace(void);

        InFace& operator+= (const InFace&);
        size_t length (void) const;
        friend std::ostream& operator<< (std::ostream& os, const InFace&);

        T& operator[] (const size_t);
        void start(void);
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
