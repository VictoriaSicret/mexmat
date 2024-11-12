#include "interface.h"

namespace InFaceLIST {

bool InFaceList::action (void) {
    size_t act = 0, n = 0, m = 0, way = 0, order = 0, pos = 0; List list; std::string word;
    std::cout << "\nChoose action:\n1)Push\n2)Pop\n3)Clear\n4)Link\n5)Sort" << std::endl;
    std::cin >> act;
            
    if (act != 1 && act != 2 && act != 3 && act != 4 && act != 5) return true;
    
    std::cout << "\nChoose number" << ((act == 4) ? "s" : "") << " of lists:" << std::endl;
    std::cin >> n;
    if (n >= num) return true;
                
    if (act == 4) {
        std::cin >> m;
        if (m >= num) return true;
    }

    if (act == 3) {
        vars[n].clear();
    } else {
        std::cout << "\n1)Print\n2)Save\n3)Print and save" << std::endl;
        std::cin >> way;
        if (way != 1 && way != 2 && way != 3) return true;

        if (act == 5) {
            std::cout << "\nChoose order:\n1)Lexicographic order\n2)Order on length" << std::endl;
            std::cin >> order;
        
            if (order != 1 && order != 2) return true;
            list = vars[n].sort((order == 1) ? cmp : cmplen);
        
        } else if (act == 4) {
            list = vars[n].add(&vars[m]);
        } else {
            std::cout << "\nEnter position:" << std::endl;
            std::cin >> pos;
            if (pos > vars[n].length()) return true;   

            if (act == 1) {
                std::cout << "\nEnter word:" << std::endl;
                std::cin >> word;
                list = vars[n];
                list.pushIn(pos, word);
            } else {
                list = vars[n];
                list.popIn(pos);
            }
        }

        if (way == 1 || way == 3) std::cout << "\n" << list << "\n" << std::endl;
        if (way == 2 || way == 3) this->InFace<List>::operator+=(InFace<List>(list));
        
    }

    return false;
}

}
