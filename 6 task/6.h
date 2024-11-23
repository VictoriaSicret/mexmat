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
}

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

        void del_case1(node<K, V>* n);
        void del_case2(node<K, V>* n);
        void del_case3(node<K, V>* n);
        void del_case4(node<K, V>* n);
        void del_case5(node<K, V>* n);
        void del_case6(node<K, V>* n);

        void replace(node<K,V>* n, node<K, V>* child) {
            child->parent = n->parent;
            if (n->parent->left == n) n->parent->left = child;
            else n->parent->right = child;
        }

        void delChild(node<K, V>* n) {
            node<K, V>* child = (n->right == &node::null) ? n->left : n->right;
            replace(n, child);
            if (n->color == BLACK) {
                if (child->color == RED) child->color = BLACK;
                else del_case1(child);
            }
            delNode(n);
        }

        void del_case1(node<K, V>* n) {
            if (n->parent != &node::null) {
                del_case2(n);
            }
        }

        void del_case2(node<K, V>* n) {
            node<K, V>* b = n->brother();
            if (b->color == RED) {
                n->parent->color = RED;
                b->color = BLACK;
                if (n->parent->left == n) rotateL(n->parent);
                else rotateR(n->parent);
            }
            del_case3(n);
        }

        void del_case3(node<K, V>* n) {
            node<K, V>* b = n->brother();
            if (n->parent->color == BLACK && b->color == BLACK && b->left->color == BLACK && b->right->color == BLACK) {
                b->color = RED;
                del_case1(n->parent);
            }
            else del_case4(n);
        }

        void del_case4(node<K, V>* n) {
            node<K, V>* b = n->brother();
            if (n->parent->color == RED && b->color == BLACK && b->left->color == BLACK && b->right->color == BLACK) {
                b->color = RED;
                n->parent->color = BLACK;
            } else del_case5(n);
        }

        void del_case5(node<K, V>* n) {
            node<K, V>* b = n->brother();
            if (n->parent->left == n && b->left->color == RED && b->right->color == BLACK) {
                b->color = RED;
                b->left->color = BLACK;
                rotateR(b);
            } else if (n->parent->right == n && b->left->color == BLACK && b->right->color == RED) {
                b->color = RED;
                b->right->color = BLACK;
                rotateL(b);
            }
            del_case6(n);
        }

        void del_case6(node<K, V>* n) {
            node<K, V>* b = n->brother();
            b->color = n->parent->color;
            n->parent->color = BLACK;

            if (n == n->parent->left) {
                b->right->color = BLACK;
                rotateL(n->parent);
            } else {
                b->left->color = BLACK;
                rotateR(n->parent);
            }
        }

        node<K, V>* getMin(const node<K, V>* n) {
            node<K, V>* res = n;
            if (res->left == &node::null) {
                res = res->right;
                while (res->left != &node::null) res = res->left;
            } else {
                res = res->left;
                while (res->right != &node::null) res = res->right;
            }
            return res;
        }

        void remove(node<K, V>** root, const K& key) {
            node<K, V>* n = *root;
            if (n->Key() == key) {
                if (n->left != &node::null && n->right != &node::null) {
                    node<K, V>* m = getMin(n);
                    n->key = m->key; n->value = m->value;
                    delChild(m);
                } else {
                    delChild(n);
                }

            } else if (n->Key() < key) {
                if (n->left == &node::null) return;
                remove(&n->left, key);
            } else {
                if (n->right == &node::null) return;
                remove(&n->right, key);
            }
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
            remove(&root, key);
        }
    };
}

#endif
