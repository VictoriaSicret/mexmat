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
		class Node {
			public:
                	char* mes;
                	size_t size;
                	Node* last;
                	Node* next;

                	Node(const char*, const Node*, const Node*);

                	Node(Node&&);

                	~Node();

                	Node& operator= (Node&& node);

        	        friend int cmp(const Node&, const Node&, int(*) (const char*, const char*));
	        };

		Node* head;
		Node* back;
		Node* pos;
		
		public:
	
		List(Node*, Node*);
		~List();

		void pushBack(const char*);
	};
}

#endif
