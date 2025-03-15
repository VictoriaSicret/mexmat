#ifndef TreeInFacee
#define TreeInFacee

#include "RBTREE.h"
#include <ctime>
#include <random>

namespace TReeINTERFACE {
    using namespace RBTREE;
    std::string genStr(void);

    std::string genStr(void) {
        size_t num = rand()%100 +1; std::string tmp, res; char c;
        for (size_t i = 0; i < num; ++i) {
            c = rand()%25 +98;
            res += (tmp = c);
        }
        return res;
    }

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
            srand(time(NULL));
            std::cout <<"Choose type of tree:\n1)<string, int>\n2)<string, string>" << std::endl;
            std::cin >> act; if (act != 1 && act != 2) return;
            start_(act == 1);
        }

        void start_(bool flag) {
            int act(0), actPtr(0), val(0), pos(0); size_t n(0); std::string word, value;
            while (true) {
                try {
                    std::cout << "\nChoose action:\n1)add value\n2)remove value\n3)print tree\n4)work with pointer\n5)generate tree" << std::endl;
                    std::cin >> act; if ((std::cin.fail()) || (act != 1 && act != 2 && act != 3 && act != 4 && act != 5)) break;
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
                    } else if (act == 3){
                        (flag) ? (std::cout<< fi << std::endl) : (std::cout << fs << std::endl);
                    } else if (act == 4){
                        auto iteri = fi.Root(); auto iters = fs.Root();
                        (flag) ? (std::cout<< iteri << std::endl) : (std::cout << iters << std::endl);
                        while (true) {
                            std::cout << "\nChoose action with iterator:\n1)move\n2)print tree" << std::endl;
                            std::cin >> actPtr; 
                            if ((std::cin.fail()) || (actPtr != 1 && actPtr != 2)) break;
                            if (actPtr == 1) {
                                std::cout << "\nMove:\n1)To first\n2)To last\n3)To root\n4)Next\n5)Last" << std::endl;
                                std::cin >> pos; if (pos != 1 && pos != 2 && pos != 3 && pos != 4 && pos != 5) break;
                                if (pos == 1) {
                                    if (flag) iteri = fi.begin();
                                    else iters = fs.begin();
                                } else if (pos == 2) {
                                    if (flag) iteri = fi.end();
                                    else iters = fs.end();
                                } else if (pos == 3) {
                                    if (flag) iteri = fi.Root();
                                    else iters = fs.Root();
                                } else if (pos == 4) {
                                    if (flag) ++iteri;
                                    else ++iters;
                                } else {
                                    if (flag) --iteri;
                                    else --iters;
                                }
                            } else (flag) ? (std::cout<< iteri << std::endl) : (std::cout << iters << std::endl);
                        }
                    } else {
                        std::cout << "\nEnter number of elements:" << std::endl;
                        std::cin >> n;
                        for (size_t i = 0; i < n; ++i) {
                            if (flag) fi.insert(genStr(), rand());
                            else fs.insert(genStr(), genStr());
                        }
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
