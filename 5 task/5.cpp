#include "5.h"

namespace LIST {
	const char* ListExcept::what() const noexcept {
		return message;
	}

	ListExcept::ListExcept(const char* text) {
		message = new char[strlen(text)+1];
		strcmp(message, text);
	}

	ListExcept::~ListExcept() {
		delete[] message;
	}

	List::Node::Node(char* text = nullptr, Node* last = nullptr, Node *next = nullptr): last(last), next(next) {
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

	List::Node::Node(Node&& node) {
                size = node.size;
                node.size = 0;
                mes = (node.mes == nullptr) ? nullptr : new char[size];
                memcpy(mes, node.mes, size);
                if (node.mes != nullptr) {
                        delete[] node.mes;
                }
                last = node.last;
                node.last = nullptr;
                next = node.next;
                node.next = nullptr;
        }

	List::Node::~Node() {
                size = 0;
                delete[] mes;
        }


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
}
