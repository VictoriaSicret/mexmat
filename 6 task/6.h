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

            node* brother(void) {
                return (n.parent->left == &n) ? n.parent->right : n.parent->left;
            }

            node* grandparent(void) {
                return n.parent->parent;
            }

            node* uncle(void) {
                return n.parent->brother();
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

        void insert_case1(node<K, V>* n);
        void insert_case2(node<K, V>* n);
        void insert_case3(node<K, V>* n);
        void insert_case4(node<K, V>* n);
        void insert_case5(node<K, V>* n);

        void insert_case1(node<K, V>* n) {
            if (n->parent == null) n->color = BLACK;
            else insert_case2(n);
        }

        void insert_case2(node<K, V>* n) {
            if (n->parent->color == BLACK) return;
            else insert_case3(n);
        }

        void insert_case3(node<K, V>* n) {
            node<K, V>* u = n->uncle(), g = n->grandparent();
            if (u != null && u->color == RED) {
                n->parent->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                insert_case1(g);
            } else insert_case4(n);
        }

        void insert_case4(node<K, V>* n) {
            node<K< V>* g = n->grandparent();
            if (n->parent->left == n && g->right == n->parent) n = rotateR(n->parent)->right;
            else if (n->parent->right == n && g->left == n->parent) n = rotateL(n->parent)->left;
            insert_case5(n);
        }

        void insert_case5(node<K, V>* n) {
            node<K, V>* g = n->grandparent();
            g->color = RED; n->parent->color = BLACK;
            if (g->left == n->parent) rotateR(n->parent);
            else rotateL(n->parent);
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
                insert_case1(root);
            }

            return false;
        }

        
        bool balanceRemoveL(node<K, V>** root) {
            node<K, V>* node = *root;
            node<K, V>* l = node->left; node<K, V>* r = node->right;
            if (l->color == RED) {
                l->color = BLACK;
                return false;
            }

            if (r->color == RED) {
                node->color = RED;
                r->color = BLACK;
                node = *root = rotateR(node);
                if (balanceRemoveL(&node->left)) node->left->color = BLACK;
                return false;
            }

            node<K, V>* rl = r->left; node<K, V>* rr = r->right;

            if(rl->color == BLACK && rr->color == BLACK) {
                r->color = RED;
                return true;
            }

            if(rl->color == RED) {
                r->color = RED;
                rl->color = BLACK;
                r = node->right = rotateL(r);
                rr = r->right;
            }

            if (rr->color == RED) {
                r->color = node->color;
                rr->color = node->color = BLACK;
                *root = rotateR(node);
            }
            return false;
        }

        bool balanceRemoveR(node<K, V>** root) {
            node<K, V>* node = *root;
            node<K, V>* l = node->left; node<K, V>* r = node->right;
            if (r->color == RED) {
                r->color = BLACK;
                return false;
            }

            if (l->color == RED) {
                node->color = RED;
                l->color = BLACK;
                node = *root = rotateL(node);
                if (balanceRemoveR(&node->right)) node->right->color = BLACK;
                return false;
            }

            node<K, V>* lr = l->right; node<K, V>* ll = l->left;

            if(lr->color == BLACK && ll->color == BLACK) {
                l->color = RED;
                return true;
            }

            if(lr->color == RED) {
                l->color = RED;
                lr->color = BLACK;
                l = node->left = rotateR(l);
                ll = l->left;
            }

            if (ll->color == RED) {
                l->color = node->color;
                ll->color = node->color = BLACK;
                *root = rotateL(node);
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
