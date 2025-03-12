#include "1.h"

CintN::CintN (std::string str) {
    int k = str.length();
    for (int i = 0; i < k; ++i) {
        if (!(i == 0 && (str[i] == '-' || str[i] == '+')) && !(48 <= str[i] && str[i] <= 57)) {
            std::cout << "Wrong data." << std::endl;
            exit(-1);
        }
    }
    val = str;
}

CintN& CintN::operator= (const CintN &v) {
	val = v.val;
	return *this;
}

std::ostream& operator<< (std::ostream& os, const CintN& ob) {
    return os << ob.print();
}
std::ostream& operator<< (std::ostream& os, const CintN1& ob) {
	return os << ob.print();
}

std::ostream& operator<< (std::ostream& os, const CintN2& ob) {
	return os << ob.print();
}

int Input(std::ifstream& in, std::vector <CintN*> &v) {
    int type; std::string file, value;
    while (in >> type >> file >> value) {
        if (type == 1) {
            std::ofstream f(file); f.close();
            CintN1 *w = new CintN1(file, value);
            v.push_back(w);
        }
        if (type == 2) {
            std::ofstream f(file); f.close();
            CintN2 *w = new CintN2(file, value);
            v.push_back(w);
        }
    }

    return 0;
}
