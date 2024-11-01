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

    List::List(const List& ls) {
        for (auto iter = ls.begin(); iter != ls.end(); ++iter) {
            this->pushBack(*iter);
        }
    }
    
    List::List(List&& move) {
        size = move.size;
        move.size = 0;
        head = move.head;
        move.head = nullptr;
        back = move.back;
        move.back = nullptr;
    }

    List& List::operator= (const List& ls) {
        this->clear();

        for (auto iter = ls.begin(); iter != ls.end(); ++iter) {
            auto tmp = *iter;
            this->pushBack(tmp);
            delete[] tmp;
        }

        return *this;
    }
    
    List& List::operator= (List&& move) {
        this->clear();

        size = move.size;
        move.size = 0;
        head = move.head;
        move.head = nullptr;
        back = move.back;
        move.back = nullptr;

        return *this;
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

    bool List::empty(void) const {
        return size == 0;
    }

    size_t List::length(void) const {
        return size;
    }

    List List::add(const List* curr) {
        List res = *this;
        for (auto iter = curr->begin(); iter != curr->end(); ++iter) {
            auto tmp = *iter;
            res.back->next = new Node(tmp);
            delete[] tmp;

            res.back->next->last = res.back;
            res.back = res.back->next;
            res.size++;
        }
        return res;
    }

    void List::clear (void) {
        while (size > 0) {
            this->popBack();
        }
    }
    
    List List::sort(int(*op) (const char*, const char*)) {
/*        List ls;
        for (auto iter = this->begin(); iter != this->end(); ++iter) {
            if (ls.empty()) {
                ls.pushBack(*iter);
                continue;
            }

            auto iter1 = ls.begin();
            while (iter1+1 != ls.end()) {
                if (op(*iter, *iter1) == 1) {
                    ls.pushIn(Index(iter1), *iter);
                    break;
                }
            }


        }
*/      List tmp = *this;
        double factor = 1.25;
        size_t step = tmp.size-1;
        while (step >= 1) {
            for (size_t i = 0; i +step < size; ++i) {
                auto iter = tmp.begin() + i;
                auto tmp1 = *iter; auto tmp2 = *(iter+step);
                if (op(tmp1, tmp2) == 1) {
                    swap(iter, iter+step);
                }
                delete[] tmp1; delete[] tmp2;
            }

            step /= factor;
        }

        return tmp;
    }

    void List::swap (List::iterator i1, List::iterator i2) {
        List ls;

        for (auto iter = this->begin(); iter != this->end(); ++iter) {
            if (iter == i1) {
                auto tmp = *i2;
                ls.pushBack(tmp);
                delete[] tmp;
            }
            else if (iter == i2) {
                auto tmp = *i1;
                ls.pushBack(tmp);
                delete[] tmp;
            }
            else {
                auto tmp = *iter;
                ls.pushBack(tmp);
                delete[] tmp;
            }
        }

        *this = ls;
/*
        int f1 = 0;
        if (i1.Index() == 0) f1 = 1;
        else if (i1.Index() == size-1) f1 = 2;
        
        int f2 = 0;
        if (i2.Index() == 0) f2 = 1;
        else if (i2.Index() == size-1) f2 = 2;

        

        auto tmp_l = i1.pos->last;
        auto tmp_n = i1.pos->next;
        i1.pos->last = i2.pos->last;
        i1.pos->next = i2.pos->next;
        i2.pos->last = tmp_l;
        i2.pos->next = tmp_n;

        if (f1) {
            (f1 == 1) ? head : back = i2.pos;
        }
        if (f2) {
            (f2 == 1) ? head : back = i1.pos;
        }
*/
    }
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

    List::iterator List::iterator::operator+(size_t k) {
        auto tmp = pos;
        for (size_t i = 0; i < k; ++i) {
            if (tmp != nullptr) {
                tmp = tmp->next;
            } else {
                return lst->end();
            }
        }
        return iterator(lst, tmp, index+k);
    }

    bool List::iterator::operator== (const List::iterator& i) const {
        return (lst == i.lst && index == i.index) ? true : false;
    }

    bool List::iterator::operator!= (const List::iterator& i) const {
        return !(*this == i);
    }
    
    char* List::iterator::operator* (void) const {
        return std::move(pos->val());
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

    std::ostream& operator<< (std::ostream& os, const List& list) {
        for (auto iter = list.begin(); iter != list.end(); ++iter) {
            auto tmp = *iter;
            os << tmp << "\n";
            delete[] tmp;
        }

        return os;
    }

    std::istream& operator>> (std::istream& is, List& list) {
        list.clear();
        size_t num = 0;
        is >> num;
        
        for (size_t i = 0; i < num; ++i) {
            char* tmp = nullptr;
            is >> tmp;
            list.pushBack(tmp);
            delete[] tmp;
        }

        return is;
    }

    bool stop(char c) {
        return (c == '\n' || c == ' ' || c == '\t' || c == 0);
    }

    std::istream& operator>> (std::istream& is, char*& word) {
        if (word != nullptr) delete[] word;

        char c; size_t count = 0; bool flag = false;
        is >> c;
        if (!stop(c)) {
            word = new char[2];
            count++;
            word[0] = c;
            word[1] = 0;
            flag = true;
        }
        
        while(!flag || !stop(c)) {
            is.get(c);
            if (!flag && stop(c)) continue;
            if (flag && stop(c)) break;
            char* tmp = new char[count+2];
            for (size_t i = 0; i < count; ++i) {
                tmp[i] = word[i];
            }
            tmp[count] = c;
            tmp[count+1] = 0;
            count++;
            delete[] word;
            word = tmp;
            flag = true;
        }
        return is;
    }

}

