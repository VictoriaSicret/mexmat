#include "interface.h"

namespace INTERFACE {
    InFace::InFace (void) {
        num = 0;
        vars = nullptr;
    }

    InFace::InFace (const List& curr) {
        num = 1;
        vars = new List[num];
        vars[0] = curr;
    }

    InFace::~InFace (void) {
        delete[] vars;
    }

    InFace& InFace::operator+= (const InFace& inface) {
        num += inface.num;
        auto tmp = new List[num];
        for (size_t i = 0; i < num; ++i) {
            tmp[i] = (i < num - inface.num) ? vars[i] : inface.vars[i+inface.num-num];
        }

        delete[] vars;
        vars = tmp;
        return *this;
    }
    
    size_t InFace::length (void) const {
        return num;
    }

    std::ostream& operator<< (std::ostream& os, const InFace& inface) {
        for (size_t i = 0; i < inface.length(); ++i) {
            os << inface.vars[i] << "\n";
        }

        return os;
    }

    List& InFace::operator[] (const size_t k) {
        if (k >= num) throw ListExcept("out of interface");

        return vars[k];
    }
    
    void func(void) {
        InFace I; int act1 = 0, act2 = 0, way = 0, order = 0; size_t n = 0, m = 0, pos = 0; List list; std::string word;
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
                        std::cout << "\nChoose order:\n1)Lexicographic order\n2)Order on length" << std::endl;
                        std::cin >> order;
                        if (order != 1 && order != 2) break;
                        list = I[n].sort((order == 1) ? cmp : cmplen);
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
	}

}
