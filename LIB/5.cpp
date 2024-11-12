#include "5.h"

namespace LIST {
	List::Node::Node(const std::string text): mes(text) {
        next = nullptr;
        last = nullptr; 
    }

	List::Node::~Node() {
        last = nullptr;
        next = nullptr;
    }

    int cmp (const std::string str1, const std::string str2) {
        if (cmplen(str1, str2) != 0) return cmplen(str1, str2);
        if (str1 > str2) return 1;
        if (str1 < str2) return -1;

        return 0;
    }
    
    int cmplen (const std::string str1, const std::string str2) {
        if (str1.length() < str2.length()) return -1;
        if (str1.length() > str2.length()) return 1;
        return 0;
    }

    std::string List::Node::val(void) const {
        return mes;
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
        size = 0;
        for (auto iter = ls.begin(); iter != ls.end(); ++iter) {
            if (size == 0) {
                back = new Node(*iter);
                head = back;
                size++;
                continue;
            }
            back->next = new Node(*iter);
            back->next->last = back;
            back = back->next;
            size++;
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
        if (ls.empty()) return *this;
        for (auto iter = ls.begin(); iter != ls.end(); ++iter) {
            this->pushBack(*iter);
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

	void List::pushBack(const std::string text) {
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
    
    void List::pushHead(const std::string text) {
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

    void List::pushIn(const size_t k, const std::string text) {
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
        auto block = new Node(text);

        iter.pos->last->next = block;
        block->next = iter.pos;
        block->last = iter.pos->last;
        iter.pos->last = block;
        size++;
    } 

    void List::popIn(const size_t k) {
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

    bool List::empty(void) const {
        return size == 0;
    }

    size_t List::length(void) const {
        return size;
    }

    List List::add(const List* curr) {
        List res = *this;
        for (auto iter = curr->begin(); iter != curr->end(); ++iter) {
            res.back->next = new Node(*iter);

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
    
    List List::sort(int (*op)(const std::string, const std::string)) {
        List tmp; bool flag = true;
        for (auto iter = this->begin(); iter != this->end(); ++iter) {
            if (tmp.empty()) {
                tmp.pushBack(*iter);
                continue;
            }

            for (auto it = tmp.begin(); it != tmp.end(); ++it) {
                if (op(*iter, *it) == 1) continue;
                else {
                    tmp.pushIn(it.Index(), *iter);
                    flag = false;
                    break;
                }
            }
            if (flag) tmp.pushBack(*iter); 
            else flag = true;

        }
        return tmp;
    }

    void List::swap (List::iterator i1, List::iterator i2) {
        List ls;
        
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
        if (pos == nullptr) return *this;
        pos = pos->next;
        index++;
        return *this;
    }

    List::iterator List::iterator::operator++(int) {
        if (pos == nullptr) return *this;
        iterator old = *this;
        ++(*this);
        return old;
    }

    List::iterator& List::iterator::operator--(void) {
        if (pos == nullptr) return *this;
        pos = pos->last;
        index--;
        return *this;
    }

    List::iterator List::iterator::operator--(int) {
        if (pos == nullptr) return *this;
        iterator old = *this;
        --(*this);
        return old;
    }

    List::iterator List::iterator::operator+(size_t k) {
        if (pos == nullptr) return *this;
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
    
    std::string List::iterator::operator* (void) const {
        return pos->mes;
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

	std::string List::name (void) {
		return std::string("List");
	}

    std::ostream& operator<< (std::ostream& os, const List& list) {
        if (list.empty()) return os << "\n";
        for (auto iter = list.begin(); iter != list.end(); ++iter) {
            os << *iter << "\n";
        }

        return os;
    }

    std::istream& operator>> (std::istream& is, List& list) {
        list.clear();
        size_t num = 0;
        is >> num;
        
        for (size_t i = 0; i < num; ++i) {
            std::string tmp;
            is >> tmp;
            list.pushBack(tmp);
        }

        return is;
    }

}

