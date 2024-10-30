#include "5.h"

namespace LIST {
    //ListExcept BEGIN

	const char* ListExcept::what() const noexcept {
		return message;
	}

	ListExcept::ListExcept(const char* text) {
		message = new char[strlen(text)+1];
		strcpy(message, text);
	}

	ListExcept::~ListExcept() {
		delete[] message;
	}

    //ListExcept END

    //List::Node BEGIN

	List::Node::Node(const char* text = nullptr, const Node* l = nullptr, const Node *n = nullptr){
        last = l; next = n;
        if (text != nullptr) {
            size = strlen(text)+1;
            mes = new char[size];
            for (size_t i = 0; i < size; ++i) {
                mes[i] = text[i];
            }
        } else {
            mes = nullptr;
            size = 0;
        }
    }
    
	List::Node::~Node() 
        size = 0;
        delete[] mes;
    }

    char* List::Node::val(void) const {
        char* res = new char[size];
        strcpy(res, mes);
        return res;
    }
    
    int List::cmp(const Node& n1, const Node& n2, int (*op)(const char*, const char*)) {
        return op(n1.mes, n2.mes);
    }
    
    //List::Node END

    //List BEGIN

	List::List(Node* front = nullptr, Node* end = nullptr): head(front), back(end), pos(front) {
		if ((front == nullptr && end != nullptr) || (front != nullptr && end == nullptr)) {
			throw ListExcept("Wrong front or end");
		}	
	}
        
	List::~List() {
		pos = nullptr;
		if (head != nullptr) {
			while (back != head) {
				auto tmp = back->last;
				delete[] back;
				back = tmp;
				back->last = nullptr;
			}

			delete[] head;
		}
	}

	void List::pushBack(const char* text) {
		back->next = new Node(text);
		back->next->last = back;
		back = back->next;
	}

    void List::popBack(void) {
        if (back == head) {
            delete[] back;
            back = head = nullptr;
        } else {
            back = back->last;
            delete[] back->next;
            back->next = nullptr;
        }
    }
    
    void List::pushHead(const char* text) {
        head->last = new Node(text);
        head->last->next = head;
        head = head->last;
    }

    bool List::empty(void) {
        return (head == nullptr) ? true : false;
    }

    size_t List::length(void) {
        if (head == nullptr) return 0;
        auto tmp = head; size_t count = 1;
        while (tmp != back) {
            tmp = tmp->next;
            count++;
        }
        return count;
    }

    List List::add(const List& curr) {
        end->next = curr->head;
        end = curr->end;
    }

    //List END

    //List::iterator BEGIN

    List::iterator::iterator(List* lst = nullptr, Node* node = nullptr): lst(lst), pos(node) {}

    List::iterator::~iterator(void) {
        lst = nullptr;
        pos = nullptr;
    }

    iterator& List::iterator::operator++(void) {
        pos = pos->next;
        return *this;
    }

    iterator List::iterator::operator++(int k) {
        iterator old = *this;
        ++(*this);
        return old;
    }

    iterator& List::iterator::operator--(void) {
        pos = pos->last;
        return *this;
    }

    iterator List::iterator::operator--(int k) {
        iterator old = *this;
        --(*this);
        return old;
    }

    bool List::iterator::operator== (const iterator& i) const {
        return (lst == i.lst && pos == i.pos) ? true : false;
    st}

    bool List::iterator::operator!= (const iterator& i) const {
        return !(*this == i);
    }
    
    char* List::iterator::operator* (void) const {
        return pos->val();
    }
    //List::iterator END
}

