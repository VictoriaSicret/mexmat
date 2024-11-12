#ifndef LIB5
#define LIB5

#include "LIB.h"

namespace LIST {
    using namespace EXCEPT;
	class List {

		class Node {
            public:
            
            std::string mes;
            Node* last;
            Node* next;

            Node(const std::string);
            ~Node();
            
            std::string val(void) const;
        };

        class iterator {
            public:
            const List *lst;
            Node* pos;
            size_t index;

            iterator(const List*, Node*, const size_t);
            ~iterator(void);

            iterator& operator++(void);
            iterator operator++(int);
            iterator operator+ (size_t);
            iterator& operator--(void);
            iterator operator--(int);

            bool operator== (const iterator&) const;
            bool operator!= (const iterator&) const;

            std::string operator* (void) const;
            size_t Index (void);
        };
        
		Node* head;
		Node* back;
        size_t size;
		
		public:

		List(void);
		~List(void);

        List(const List&);
        List(List&&);
        List& operator= (const List&);
        List& operator= (List&&);

		void pushBack(const std::string);
        void popBack(void);

        void pushHead(const std::string);
        void popHead(void);

        void pushIn(const size_t, const std::string);
        void popIn(const size_t);        

        bool empty(void) const;
        size_t length(void) const;
        
        List add(const List*);
        void clear(void); 
	    
        List sort(int (*)(const std::string, const std::string));
        
        void swap (iterator, iterator);

        iterator begin(void) const;
        iterator end(void) const;

		static std::string name (void);
    };
    
    int cmp (const std::string, const std::string);
    int cmplen (const std::string, const std::string); 
    
    std::istream& operator>> (std::istream&, List&);
    std::ostream& operator<< (std::ostream&, const List&);
}

#endif
