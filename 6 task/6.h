#ifndef LIB6
#define LIB6

#include "EXCEPT.h"

namespace PAIR {
    template <typename T, typename K>
    class pair {
        T First;
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

        pair& operator= (const pair& p) {
            First = p.First;
            Second = p.Second;
        }

        T& first(void) {
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

            T key; L value;
            COLOR color;
            node* parent;
            node* left;
            node* right;

            static node null;
            node(T, L, COLOR);

            null(T(), L(), BLACK);

            node(T k = T(), L val = L(), COLOR c = RED): {
                key = k; value = val;
                color = c;
                parent = &null;
                left = &null;
                right = &null;
            }

            ~node(void) {
                parent = nullptr;
                left = nullptr;
                right = nullptr;
            }

            node& operator= (const node& n) {
                key = n.key; value = n.value;
                color = n.color;
                parent = n.parent;
                left = n.left;
                right = n.right;
            }

            T& Key(void) const{
                return key;
            }

            L& Value(void) const {
                return value;
            }

        };

        node<V, K>* root;
        size_t num;

        private:

        node<K, V>* newNode(const K& key, const V& value) {
            ++num;
            node<V, K>* res = new node<K, V>(key, value);
            return res;
        }

        void delNode(node<K, V>* n) {
            --num;
            delete n;
        }

        void clear(node<K, V>* n) {
            if (n == &node::null) return;
            clear(n->left);
            clear(n->right);
            delNode(n);
        }

        node<K, V>* grandparent(const node<K, V>* n) {
            return n->parent->parent;
        }

        node<K, V>* uncle(const node<K, V>* n) {
            auto grand = this->grandparent(n);
            return (grand->left == n) ? grand->right : grand->left;
        }

        node<K, V>* rotateL(node<K, V>* a) {
            auto b = a->right;
            auto med = b->left; 
            b->left = a;
            a->right = med;
            b->parent = a->parent;
            a->parent = b;
            return b;
        }

        node<K, V>* rotateR(node<K, V>* n) {
            auto b = a->left;
            auto med = b->right; 
            b->right = a;
            a->left = med;
            b->parent = a->parent;
            a->parent = b;
            return b;
        }

        void balanceInsert(node<K, V>** n) {
            node<K, V>* node = *n;
            if (node->color == RED) return;

            node<K, V>* l = node->left, r = node->right;
            if (l->color == RED) {
                if (l->right->color == RED) l = node->left = rotateL(l);
                node<K, V> ll = l->left;
                if (ll->color == RED) {
                    node->color = RED;
                    l->color = BLACK;
                    if (r->color == RED) {
                        ll->color = RED;
                        r->color = BLACK;
                        return;
                    }

                    *root = rotateR(node);
                    return;
                }
            }

            if (r->color == RED) {
                if (r->left->color == RED) r = node->right = rotateR(r);
                node<K, V> rr = r->right;
                if (rr->color == RED) {
                    node->color = RED;
                    r->color = BLACK;
                    if (l->color == RED) {
                        rr->color = RED;
                        l->color = BLACK;
                        return;
                    }

                    *root = rotateL(node);
                    return;
                }
            }
        }

        bool insert(const K& key, const V& value, node<K, V>** root) {
            node<K, V>* node = *root;
            if (node == &node::null) *root = newNode(key, value);
            else {
                if (key == node->key) {
                    node->value = value;
                    return true;
                }
                if (insert(key, value, key < node->key ? &node->left : &node->right)) return true;
                balanceInsert(root);
            }

            return false;
        }

        public:

        RBTree(void) {
            root = &node::null;
        }

        RBTree(node<K, V>* n) {
            root = n;
        }

        bool empty(void) {
            return num == 0;
        }

        size_t Num(void) {
            return num;
        }

        void clear(void) {
            clear(root);
            root = &node::null;
        }

        ~RBTree(void) {
            this->clear();
        }

        bool find(const K& key, V& value) {
            if (this->empty) return false;
            node<K, V>* n = root;
            while (n != &node::null) {
                if (n->Key() == key) {
                    value = n->Value();
                    return true;
                }
                n = (n->Key() < key) ? n->left : n->right;
            }

            return false;
        }

        V& operator[] (const K& key) {
            V tmp;
            if (find(key, tmp)) return tmp;
            else throw Except("invalid key");
        }

        void insert(const K& key, const V& value) {
            insert(key, value, &root);
            root->color = BLACK;
        }

        void remove(const K& key) {
            if (!(this->empty())) {
                if (root->Key() < key) {
                    RBTree tmp(root->left);
                    tmp.remove(key);
                } else if (root->Key() > key) {
                    RBTree tmp(root->right);
                    tmp.remove(key);
                } else {
                    if (root->left == nullptr && root->right == nullptr) {

                        if (root->parent == nullptr) {
                            delete root;
                            return;
                        }

                        (root->parent->left == root) ? root->parent->left = nullptr : root->parent->right = nullptr;
                        delete root;

                    } else if ((root->left != nullptr && root->right == nullptr) || (root->left == nullptr && root->right != nullptr)) {

                        auto tmp = (root->left != nullptr) ? root->left : root->right;
                        tmp->parent = root->parent;
                        auto old = root;
                        root = tmp;
                        delete old;

                    } else if (root->right->left == nullptr) {
                        auto tmp = root->right;
                        root->right = root->right->right;
                        root->key_value = tmp->key_value;
                        root->color = tmp->color;
                        delete tmp;
                    } else {
                        auto tmp = root->right->left;
                        while(tmp->left != nullptr) tmp = tmp->left;
                        root->key-value = tmp->key_value;
                        root->color = tmp->color;
                        RBTree pp(tmp);
                        pp.remove(tmp->Key());
                    }
                }
            }
        }

        
    };
}

#endif
