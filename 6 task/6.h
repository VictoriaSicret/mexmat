#ifndef LIB6
#define LIB6

#include "EXCEPT.h"

namespace PAIR {
    template <typename T, typename K>
    class pair {
        const T First;
        K Second;
        public:

        pair(void) {
            First = T();
            Second = K();
        }

        pair (const T& first): First(first) {
            Second = K();
        }

        pair(const T& first, const K& second): First(first), Second(second) {}

        ~pair(void) {}

        const T& first(void) const {
            return First;
        }

        V& second(void) {
            return Second;
        }
    }
}`

namespace RBTREE {
    enum COLOR {RED, BLACK};

    using namespace PAIR;
    using namespace EXCEPT;
    template <typename K, typename V>
    class RBTree {
        template <typename T, typename L>
        class node {
            public:
            pair<T, L> key_value;
            COLOR color;
            node* parent;
            node* left;
            node* right;

            node(T k = T(), L val = L()): {
                key_value = pair<T, L>(k, val);
                color = red;
                parent = nullptr;
                left = nullptr;
                right = nullptr;
            }

            ~node(void) {
                parent = nullptr;
                left = nullptr;
                right = nullptr;
            }

            void makeLeftParent(node* n) {
                n->left = this;
                this->parent = n;
            }

            const T& Key(void) const{
                return key_value.first();
            }

            L& Value(void) const {
                return key_value.second();
            }

            void makeRightParent(node* n) {
                n->right = this;
                this->parent = n;
            }

            void makeLeftChild(node* n) {
                n->parent = this;
                this->left = n;
            }

            void change(void) {
                if (color = RED) color = BLACK;
                else color = RED;
            }

            void makeRightChild(node* n) {
                n->parent = this;
                this->right = n;
            }

            bool operator< (const node& n) {
                return key_value.first < n.key_value.first;
            }

            bool operator> (const node& n) {
                return key_value.first > n.key_value.first;
            }

            bool operator== (const node& n) {
                return key_value.first == n.key_value.first;
            }

            bool operator!= (const node& n) {
                return key_value.first  n.key_value.first;
            }

            bool operator<= (const node& n) {
                return key_value.first <= n.key_value.first;
            }

            bool operator>= (const node& n) {
                return key_value.first >= n.key_value.first;
            }

        }

        template <typename T, typename L>
        class iterator {
            const RBTree<T, L>* tree;
            node<T, L>* pos;
            node<T, L>* old;

            public:

            iterator(const RBTree<T, L>* t, const node<T, L>* p, const node<T, L>* o) {
                tree = t; pos = p; old = o;
            }

            ~iterator(void) {
                tree = nullptr;
                pos = nullptr;
                old = nullptr;
            }

            iterator operator~(void) {
                if (old == nullptr) {
                    pos = nullptr;
                    old = nullptr;
                }

                pos = old;
                old = pos->parent;
            }

            iterator operator++(void) {
                old = pos;
                pos = pos->right;
            }

            iterator operator--(void) {
                old = pos;
                pos = pos->left;
            }

            pair<T, L>& operator*(void) {
                if (pos != nullptr) return pos;
                return node();
            }

        }

        node<K, V>* root;

        iterator<K, V> begin(void) {
            return iterator(this, root, nullptr);
        }

        public:

        RBTree(void) {
            head = nullptr;
        }

        RBTree(node<K, V>* head) {
            root = head;
        }

        bool empty(void) {
            return head == nullptr;
        }

        void clear(void) {
            if (this->empty()){
            } else if (head->left == nullptr && head->right == nullptr) {
                delete root;
            } else {
                RBTree l(root->left);
                RBTree r(root->right);
                l.clear();
                r.clear();
                delete root;
            }
        }

        ~RBTree(void) {
            this->clear();
        }

        bool find(const K& key, V& value) {
            if (this->empty) return false;
            if (head.Key() == key) {
                value = head.Value();
                return true;
            } else if (head.Key() < key) {
                RBTree tmp(head->left);
                return tmp->find(key, value);
            } else {
                RBTree tmp(head->right);
                return tmp->find(key, value);
            }
        }

        V& operator[] (const K& key) {
            V tmp;
            if (find(key, tmp)) return tmp;
            else throw Except("invalid key");
        }

        void insert(const K& key, const V& value) {
            if (this->empty)
        }
    }
}

#endif
