#ifndef LIB6
#define LIb6

namespace RBTREE {
    template <typename T>
    class RBTree {
        template <typename V>
        class node {
            public:
            V value;
            node* parent;
            node* left;
            node* right;
        }
    }
}

#endif
