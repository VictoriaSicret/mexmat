#ifndef TreeInFacee
#define TreeInFacee

#include "RBTREE.h"

namespace TReeINTERFACE {
    using namespace RBTREE;
    class TreeInFace {
        RBTree<std::string, int> fi;
        RBTree<std::string, std::string> fs;
        public:
        TreeInFace (void): fi(), fs(){}
        ~TreeInFace (void) {}

        TreeInFace(const TreeInFace& inf): fi(inf.fi), fs(inf.fs) {}
        TreeInFace& operator= (const TreeInFace& inf) {fi = inf.fi; fs = inf.fs; return *this;}

        void start(void) {
            int act(0);
            std::cout <<"Choose type of tree:\n1)<string, int>\n2)<string, string>" << std::endl;
            std::cin >> act; if (act != 1 && act != 2) return;
            start_(act == 1);
        }

        void start_(bool flag) {
            int act(0), val(0); std::string word, value;
            while (true) {
                try {
                    std::cout << "\nChoose action:\n1)add value\n2)remove value\n3)print tree" << std::endl;
                    std::cin >> act; if (act != 1 && act != 2 && act != 3) break;
                    if (act == 1) {
                        std::cout << "\nEnter key:" << std::endl;
                        std::cin >> word;
                        std::cout << "\nEnter value:" << std::endl;
                        ((flag) ? std::cin >> val : std::cin >> value);
                        (flag) ? (fi.insert(word, val)) : (fs.insert(word, value));
                    } else if (act == 2) {
                        std::cout << "\nEnter key:" << std::endl;
                        std::cin >> word;
                        (flag) ? (fi.remove(word)) : (fs.remove(word));
                    } else {
                        (flag) ? (std::cout<< fi << std::endl) : (std::cout << fs << std::endl);
                    }
                }
                catch (EXCEPT::Except& excp) {
                    std::cout << "\n" << excp.what() << std::endl;
                    break;
                }
            }
        }
    };
}

#endif
