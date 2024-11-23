#include "6.h"

using namespace RBTREE;
int main(void) {
    RBTree<int, int> tree; int x = 0;
    tree.insert(2, 5); tree.insert(1, 5);
    if(tree.find(2, x)) std::cout << tree[2] << " " <<x << std::endl;
    tree.remove(1);
    return 0;
}
