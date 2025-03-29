#include "3.h"

CintN::CintN (std::string str) {
    size_t k = 0; bool flag = true;
	for (size_t i = 0; i < str.length(); ++i) {
		if (!((i == 0 && str[i] == '-') || (48 <= str[i] && str[i] <= 57))) {
	        throw ExceptCintN("wrong data: " + str + "\n");
			break;
		}
		if (flag && str[i] != '0') {
			flag = false;
			k = i;
		}
	}
    val = str.substr(k);
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
    int i = val.length()-1, j = ob.val.length()-1, p = 0, dop = 0; std::string res = "";
    while (i > -1 && j > -1) {
		dop = (val[i]-48) + (ob.val[j]-48) + p;
		res =  std::to_string(dop%10) + res;
		p = dop/10;
		--i; --j;
    }
    while (i >= 0) {
		dop = (val[i] - 48) + p;
		res = std::to_string(dop%10) + res;
		p = dop/10;
		--i;
    }
    while (j >= 0) {
		dop = (ob.val[j] - 48) + p;
        res = std::to_string(dop%10) + res;
        p = dop/10;
        --j;
    }
	if (p == 1) res = "1"+res;

    return CintN(res);
}

CintN& CintN::operator+= (const CintN &v) {
	*this = *this + v;
	return *this;
}

CintN CintN::operator+ () const{
	return CintN(val);
}

CintN CintN::operator- () const{
    if (val == "0") return CintN("0");
    std::string res = val;
    if (res[0] == '-') res = res.substr(1);
    else res = "-" + res;
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
		res = std::to_string(diff) + res;
	    --i; --j;
	}

    while (i > -1) {
		diff = (val[i]-48) + p;
        if (diff < 0) {
			diff += 10;
            p = -1;
        } else p = 0;
        res = std::to_string(diff) + res;
        --i;
    }
    return CintN(res);

}

CintN CintN::operator* (const CintN& ob) const {
    bool s1 = (val[0] == '-') ? false : true; bool s2 = (ob.val[0] == '-') ? false : true;
	
	if (!s1 && !s2) return (-(*this))*(-ob);
	if (!s1 && s2) return -((-(*this))*ob);
	if (s1 && !s2) return -((*this)*(-ob));

	if (val.size() > ob.val.size()) return ob*(*this);	
	std::string buff; int dop{}, p{}; CintN res("0");
	for (size_t i = ob.val.size(); i >= 1; --i) {
		for (size_t j = val.size(); j >= 1; --j) {
			dop = (val[j-1]-48)*(ob.val[i-1]-48) + p;
			buff =  std::to_string(dop%10) + buff;
			p = dop/10;
		}
		if (p != 0) buff = std::to_string(p) + buff;	
		for (size_t k = 0; k < (ob.val.size()-i); ++k) buff += "0";
		res += CintN(buff);
		buff = ""; p = 0;
	}

	return res;
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

std::string genString(size_t n) {
	std::string res;
	size_t num = std::rand()%(n-1) +1;
//	bool flag = (std::rand()%2 == 0) ? true : false;	
	for (size_t i = 0; i < num; ++i) {
		std::string tmp(std::to_string(std::rand()%10));
		if (res.empty() && tmp == "0") continue;
		else res += tmp;
	}
//	if (!res.empty() && !flag) res = "-" + res;
	if (res.empty()) res = "0";
	return res;
}

void gen(std::ofstream& os, size_t n, size_t k) {
	for (size_t i = 0; i < n; ++i) {
		os << genString(k) << " ";
	}
}

CintN CintN2::operator* (const CintN& ob) const {
    bool s1 = (val[0] == '-') ? false : true; bool s2 = (ob.val[0] == '-') ? false : true;
	
	if (!s1 && !s2) return (-(*this))*(-ob);
	if (!s1 && s2) return -((-(*this))*ob);
	if (s1 && !s2) return -((*this)*(-ob));

	if (val.size() > ob.val.size()) return ob*(*this);	
	CintN res("0");

	#pragma omp declare reduction(+:CintN:omp_out+=omp_in)initializer(omp_priv=omp_orig)
	#pragma omp parallel for reduction(+:res)
	for (size_t i = ob.val.size(); i >= 1; --i) {
		std::string buff; int dop{}, p{};
		for (size_t j = val.size(); j >= 1; --j) {
			dop = (val[j-1]-48)*(ob.val[i-1]-48) + p;
			buff =  std::to_string(dop%10) + buff;
			p = dop/10;
		}
		if (p != 0) buff = std::to_string(p) + buff;	
		for (size_t k = 0; k < (ob.val.size()-i); ++k) buff += "0";
		res += CintN(buff);
		buff = ""; p = 0;
	}

	return res;
}

int Input(int type, std::ifstream& in1, std::ifstream& in2, std::vector <CintN*> &v1, std::vector<CintN*> &v2, std::vector<CFabric*> &fab) {
    std::string value;
    while (in1 >> value) v1.push_back(fab[type] -> Create(value));
	while (in2 >> value) v2.push_back(fab[type] -> Create(value));
    if (v1.size() != v2.size()) return -1;
	return 0;
}
