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


	List::Node::Node(const char* text = nullptr){
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
        next = last = nullptr;
    }
    
	List::Node::~Node() {
        size = 0;
        last = nullptr;
        next = nullptr;
        delete[] mes;
    }

    char* List::Node::val(void) const {
        char* res = new char[size];
        strcpy(res, mes);
        return res;
    }
    
    int cmp(const List::Node& n1, const List::Node& n2, int (*op)(const char*, const char*)) {
        return op(n1.mes, n2.mes);
    }
    
    //List::Node END

    //List BEGIN

	List::List(void){
		head = nullptr;
        back = nullptr;
        size = 0;
	}
        
	List::~List() {
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

	void List::pushBack(const char* text) {
        if (size == 0) {
            back = new Node(text);
            head = back;
            size = 1;
            return;
        }
		back->next = new Node(text);
		back->next->last = back;
		back = back->next;
        size++;
	}

    void List::popBack(void) {
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
    
    void List::pushHead(const char* text) {
        if (size == 0) {
            head = new Node(text);
            back = head;
            size = 1;
            return;
        }
        head->last = new Node(text);
        head->last->next = head;
        head = head->last;
        size++;
    }

    void List::popHead(void) {
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

    void List::pushIn(const size_t k, const char* text) {
        if (k > size) throw ListExcept("out of range");
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
        auto block = new Node(text);

        iter.pos->last->next = block;
        block->next = iter.pos;
        block->last = iter.pos->last;
        iter.pos->last = block;
        size++;
    } 

    void List::popIn(const size_t k) {
        if (k > size) throw ListExcept("out of range");
        if (k == 0) {
            this->popHead();
            return;
        }
        if (k == size) {
            this->popBack();
            return;
        }

        auto iter = this->begin();
        for (size_t i = 0; i < k; ++i) ++iter;
        iter.pos->last->next = iter.pos->next;
        iter.pos->next->last = iter.pos->last;
        delete iter.pos;
        size--;
    }

    bool List::empty(void) {
        return size == 0;
    }

    size_t List::length(void) {
        return size;
    }

    List& List::add(const List* curr) {
        for (auto iter = curr->begin(); iter != curr->end(); ++iter) {
            auto tmp = *iter;
            back->next = new Node(tmp);
            delete[] tmp;

            back->next->last = back;
            back = back->next;
            size++;
        }
        return *this;
    }

    void List::clear (void) {
        while (size > 0) {
            this->popBack();
        }
    }
    
/*    void sort(int(*op) (const char*, const char*)) {
        return;
    }
*/
    //List END

    //List::iterator BEGIN

    List::iterator::iterator (const List* list = nullptr, Node* node = nullptr, const size_t ind = 0): index(ind) {
        lst = list;
        pos = node;
    }

    List::iterator::~iterator(void) {
        lst = nullptr;
        pos = nullptr;
    }

    List::iterator& List::iterator::operator++(void) {
        pos = pos->next;
        index++;
        return *this;
    }

    List::iterator List::iterator::operator++(int) {
        iterator old = *this;
        ++(*this);
        return old;
    }

    List::iterator& List::iterator::operator--(void) {
        pos = pos->last;
        index--;
        return *this;
    }

    List::iterator List::iterator::operator--(int) {
        iterator old = *this;
        --(*this);
        return old;
    }

    bool List::iterator::operator== (const List::iterator& i) const {
        return (lst == i.lst && index == i.index) ? true : false;
    }

    bool List::iterator::operator!= (const List::iterator& i) const {
        return !(*this == i);
    }
    
    char* List::iterator::operator* (void) const {
        return pos->val();
    }

    size_t List::iterator::Index (void) {
        return index;
    }
//List::iterator END

    List::iterator List::begin(void)  const{
        return iterator(this, head, 0);
    }

    List::iterator List::end(void) const {
        return iterator(this, back->next, size);
    }
}

