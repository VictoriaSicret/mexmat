#include "1.h"

CintN::CintN(char arr[N+1]) {
	for (int i = 0; i < N+1; i++) {
		val[i] = arr[i];
	}
}

CintN::CintN (std::string str) {
    int k = str.length();
    if (k > N+1) exit(-1);
    for (int i = 0; i < k; ++i) {
        if (!(i == 0 && (str[i] == '-' || str[i] == '+')) && !(48 <= str[i] && str[i] <= 57)) {
            std::cout << "Wrong data." << std::endl;
            break;
        }
        val[i] = str[i];
    }
    for (int i = k; i < N+1; i++) val[i] = 0;
}

CintN::CintN(int value = 0) {
	int k = 0; int arr[N]; bool flag = false;
    if (value < 0) {
        flag = true;
        value *= -1;
    }
	while (k < N) {
		arr[k] = value%10 +48;
		value /= 10;
		k++;
	}
    if (flag) val[0] = '-';
    else val[0] = '+';

    for (int i = 1; i < N+1; ++i) val[i] = arr[N - i];
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
            std::ofstream f; f.close();
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
