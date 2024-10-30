#ifndef LIB5
#define LIB5

#include <exception>
#include <cstring>

namespace LIST {
	class ListExcept: public std::exception {
		char* message;
		public:
		ListExcept(const char*);
		~ListExcept();
		const char* what() const noexcept override;
	};
	
	class List {
        class Node;
        class iterator;

		class Node {
			friend class iterator;
            public:
            
            char* mes;
            size_t size;

            Node* last;
            Node* next;

            Node(const char*, const Node*, const Node*);
            ~Node();
                    
            char* val(void) const;

        	friend int cmp(const Node&, const Node&, int(*) (const char*, const char*));
	    };

		Node* head;
		Node* back;
        size_t size;
		
		public:

		List(void);
		~List(void);

		void pushBack(const char*);
        void popBack(void);

        void pushHead(const char *);
        void popHead(void);

        bool empty(void);
        size_t length(void);
        
        List& add(const List&);

        class iterator {
            List *lst;
            Node* pos;

            public:
            iterator(List*, Node*);
            ~iterator(void);

            iterator& operator++(void);
            iterator operator++(int);
            iterator& operator--(void);
            iterator operator--(int);

            bool operator== (const iterator&) const;
            bool operator!= (const iterator&) const;

            char* operator* (void) const;
        };
	};
}

#endif
