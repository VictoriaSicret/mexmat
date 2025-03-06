#include "1.h"

CintN::CintN(char arr[N+1]) {
	for (int i = 0; i < N+1; i++) {
		val[i] = arr[i];
	}
}

CintN::CintN (std::string str) {
    bool flag = true; int k = str.length(), t = 0;
    for (int i = k-1; i >= 0; i--) {
        if ()
        if (str[i] < 48 || str[i] > 57) {
            std::cout << "Wrong data." << std::endl;
            break;
        }
        if (t > N-1) break;
        val[t] = str[i] - 48;
        t++;
    }

    for (int i = t; i < N; i++) val[i] = 0;
}

CintN::CintN(int value = 0) {
	int k = 0;
	while (k < N) {
		val[k] = value%10;
		value /= 10;
		k++;
	}
}
		
CintN::CintN(const CintN &v) {
	for (int i = 0; i < N; i++) {
		val[i] = v.val[i];
	}
}

CintN& CintN::operator= (const CintN &v) {
	for (int i = 0; i < N; i++) {
		val[i] = v.val[i];
	}
	
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
            CintN1 *w = new CintN1(file, value);
            v.push_back(w);
        }
        if (type == 2) {
            CintN2 *w = new CintN2(file, value);
            v.push_back(w);
        }
    }

    return 0;
}
