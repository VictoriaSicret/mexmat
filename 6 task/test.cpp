#include "RBTREE.h"

using namespace RBTREE;
int main(void) {
    RBTree<std::string, size_t> tree; size_t x = 0;
    tree.insert("first", 5); tree.insert("second", x); tree["second"] = 10; tree.insert("third", 15);
    if(tree.find("second", x)) std::cout << tree["second"] << " " <<x << std::endl;
    tree.remove("second");
    return 0;
}
