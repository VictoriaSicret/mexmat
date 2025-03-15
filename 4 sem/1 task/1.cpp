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

CintN CintN::operator+ (const CintN& ob) const{
    if (val == "0") return CintN(ob);
    if (ob.val == "0") return CintN(val);

    bool s1 = (val[0] == '-') ? false : true; bool s2 = (ob.val[0] == '-') ? false : true;
    if (!s1 && !s2) return -((-(*this)) + (-ob));
    if (s1 && !s2) return (*this - (-ob));
    if (!s1 && s2) return (ob - (-(*this)));
    int i = val.length()-1, j = ob.val.length()-1, p = 0; std::string res = "";
    while (i > -1 && j > -1) {
	res.insert(0, std::to_string(((val[i]-48) + (ob.val[j] - 48) + p)%10));
	p = ((val[i]-48) + (ob.val[j] - 48) + p)/10;
	--i; --j;
    }
    while (i > -1) {
	res.insert(0, std::to_string((val[i] - 48 + p)%10));
	p = (val[i] - 48 + p)/10;
	--i;
    }
    while (j > -1) {
        res.insert(0, std::to_string((ob.val[j] - 48 + p)%10));
        p = (val[j] - 48 + p)/10;
        --j;
    }
    return CintN(res);
}

CintN CintN::operator+ () const{
	return CintN(val);
}

CintN CintN::operator- () const{
    if (val == "0") return CintN("0");
    std::string res = val;
    if (res[0] == '-') res.erase(0, 1);
    else res.insert(0, "-");
    return CintN(res);
}

CintN CintN::operator- (const CintN& ob) const{
    if (*this == ob) return CintN("0");
    if (val == "0") return CintN(-ob);
    if (ob.val == "0") return CintN(*this);

    bool s1 = (val[0] == '-') ? false : true; bool s2 = (ob.val[0] == '-') ? false : true;
    if (!s1 && !s1) return ((-ob)-(-(*this)));
    if (s1 && !s2) return (*this)+(-ob);
    if (!s1 && s2) return -((-(*this))+ob);

    if (*this < ob) return -(ob - *this);

    int i = val.length()-1, j = ob.val.length()-1, p = 0, diff = 0; std::string res = "";
    while (i > -1 && j > -1) {
	diff = (val[i]-48) - (ob.val[j] - 48) + p; 
	if (diff < 0) {
		diff += 10;
		p = -1;
	} else p = 0;
        res.insert(0, std::to_string(diff));
        --i; --j;
    }
    while (i > -1) {
	diff = (val[i]-48) + p;
        if (diff < 0) {
                diff += 10;
                p = -1;
        } else p = 0;
        res.insert(0, std::to_string(diff));
        --i;
    }

    return CintN(res);

}

bool CintN::operator== (const CintN& ob) const {
	return val == ob.val;
}

bool CintN::operator!= (const CintN& ob) const {
	return val != ob.val;
}

bool CintN::operator< (const CintN& ob) const {
	if (*this == ob) return false;
	bool s1 = (val[0] == '-') ? false : true; bool s2 = (ob.val[0] == '-') ? false : true;
	
	if (!s1 && s2) return true;
	if (s1 && !s2) return true;
	if (!s1 && !s2) return !((-ob) < (-(*this)));
	
	if (val.length() < ob.val.length()) return true;
	if (val.length() > ob.val.length()) return false;
	
	for (size_t i = 0; i < val.length(); ++i) {
		if (val[i] < ob.val[i]) return true;
		if (val[i] > ob.val[i]) return false;
	}
	return false;
}

bool CintN::operator<= (const CintN& ob) const{
	return (*this < ob) || (*this == ob);
}

bool CintN::operator> (const CintN& ob) const{
	return !(*this <= ob);
}

bool CintN::operator>= (const CintN& ob) const{
	return !(*this < ob);
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
