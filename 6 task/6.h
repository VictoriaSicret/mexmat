#ifndef LIB6
#define LIB6

namespace PAIR {
    template <typename T, typename K>
    class pair {
        T First;
        K Second;
        public:

        pair(T first, K second): First(first), Second(second) {}
        ~pair(void) {}

        const T& first(void) {
            return First;
        }

        const V& second(void) {
            return Second;
        }
    }
}

namespace RBTREE {
    using namespace PAIR;
    template <typename T, typename K>
    class RBTree {
        template <typename V>
        class node {
            public:
            pair<T, K> key_value;
            bool color;
            node* parent;
            node* left;
            node* right;

            node(T k, K val): {
                key_value = pair<T, K>(k, val);
                coolor = red;
                node = nullptr;
                left = nullptr;
                right = nullptr;
            }

            ~node(void) {
                node = nullptr;
                left = nullptr;
                right = nullptr;
            }

            void checkColor()

            void makeLeftParent(node* n) {
                n->left = this;
                this->parent = n;
            }

            void makeRightParent(node* n) {
                n->right = this;
                this->parent = n;
            }

            void makeLeftChild(node* n) {
                n->parent = this;
                this->left = n;
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

        node* head;
        size_t num;
    }
}

#endif
