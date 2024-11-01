#ifndef LIB5
#define LIB5

#include <exception>
#include <cstring>
#include <iostream>

namespace LIST {
	class ListExcept: public std::exception {
		char* message;
		public:
		ListExcept(const char*);
		~ListExcept();
		const char* what() const noexcept override;
	};

	class List {

		class Node {
            public:
            
            char* mes;
            size_t size;

            Node* last;
            Node* next;

            Node(const char*);
            ~Node();
                    
            char* val(void) const;
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

            char* operator* (void) const;
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

		void pushBack(const char*);
        void popBack(void);

        void pushHead(const char *);
        void popHead(void);

        void pushIn(const size_t, const char*);
        void popIn(const size_t);        

        bool empty(void) const;
        size_t length(void) const;
        
        List add(const List*);
        void clear(void); 
	    
        List sort(int(*)(const char*, const char*));
        
        void swap (iterator, iterator);

        iterator begin(void) const;
        iterator end(void) const;

        friend int cmp(const Node&, const Node&, int(*) (const char*, const char*));
    
    };
    std::istream& operator>> (std::istream&, List&);
    
    bool stop(char);

    std::ostream& operator<< (std::ostream&, const List&);
    std::istream& operator>> (std::istream&, char*&);
}

#endif
