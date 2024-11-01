#include "interface.h"

using namespace INTERFACE;
int op (const char*, const char*);

int main(void) {
    InFace I; int act1 = 0, act2 = 0, way = 0; size_t n = 0, m = 0, pos = 0; List list; char* word = nullptr;
    while (true) {
        std::cout << "\nChoose action:\n1)Add list\n2)Print\n3)Make action" << std::endl;
        std::cin >> act1;
        if (act1 != 1 && act1 != 2 && act1 != 3) {
            break;
        }
        if (act1 == 1) {
            std::cout <<"\nEnter list:" << std::endl;
            std::cin >> list;
            I += list;
        } else if (act1 == 2) {
            for (size_t i = 0; i < I.length(); ++i) {
                std::cout << "\nList number " << i << ":\n" << I[i] << std::endl;
            }
        } else {
            std::cout << "\nChoose action:\n1)Push\n2)Pop\n3)Clear\n4)Link\n5)Sort" << std::endl;
            std::cin >> act2;
            
            if (act2 != 1 && act2 != 2 && act2 != 3 && act2 != 4 && act2 != 5) {
                break;
            }
            
            std::cout << "\nChoose number" << ((act2 == 4) ? "s" : "") << " of lists:" << std::endl;
            std::cin >> n;
            if (n >= I.length()) break;
            if (act2 == 4) {
                std::cin >> m;
                if (m >= I.length()) break;
            }

            if (act2 == 3) {
                I[n].clear();
            } else {
                std::cout << "\n1)Print\n2)Save\n3)Print and save" << std::endl;
                std::cin >> way;
                if (way != 1 && way != 2 && way != 3) {
                    break;
                }

                if (act2 == 5) {
                    list = I[n].sort(op);
                } else if (act2 == 4) {
                    list = I[n].add(&I[m]);
                } else {
                    std::cout << "\nEnter position:" << std::endl;
                    std::cin >> pos;
                    if (pos > I[n].length()) {
                        break;
                    }

                    if (act2 == 1) {
                        std::cout << "\nEnter word:" << std::endl;
                        std::cin >> word;
                        list = I[n];
                        list.pushIn(pos, word);
                        delete[] word;
                    } else {
                        list = I[n];
                        list.popIn(pos);
                    }
                }

                if (way == 1 || way == 3) {
                    std::cout << "\n" << list << "\n" << std::endl;
                }

                if (way == 2 || way == 3) {
                    I += list;
                }
            }
        }
    }

    return 0;
}

int op (const char *str1, const char *str2) {
    size_t l1 = strlen(str1), l2 = strlen(str2);
    if (l1 > l2) return 1;
    else if (l1 < l2) return -1;
    size_t i = 0;
    while (i < l1) {
        if (str1[i] < str2[i]) return -1;
        else if (str1[i] > str2[i]) return 1;
        ++i;
    }

    return 0;
}
