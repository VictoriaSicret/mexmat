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

CintN CintN2::operator+ (const CintN& ob) const{
    if (val == "0") return CintN(ob);
    if (ob.val == "0") return CintN(val);

    bool s1 = (val[0] == '-') ? false : true; bool s2 = (ob.val[0] == '-') ? false : true;
    if (!s1 && !s2) return -((-(*this)) + (-ob));
    if (s1 && !s2) return (*this - (-ob));
    if (!s1 && s2) return (ob - (-(*this)));

	if (val.length() > ob.val.length()) return ob + *this;

	size_t i = val.length(), j = ob.val.length(); std::string res = "0", p = "0";
	for (size_t k = 0; k < ob.val.length(); ++k) {p += "0"; res += "0";}
	
	#pragma omp parallel for
    for (i = val.length(); i > 0; --i) {
		res[res.length()-1 - (val.length()-i)] = ((val[i-1]-48) + (ob.val[ob.val.length()-1 - (val.length() - i)] - 48))%10 + 48;
		p[p.length()-1 - (val.length()-i)-1] = ((((val[i-1]-48) + (ob.val[ob.val.length()-1 - (val.length() - i)] - 48))/10 == 0) ? '0': '1');
		--j;
	}

	#pragma omp parallel for 
    for (size_t l = ob.val.length() - val.length();l > 0; --l) {
        res[res.length()-1 - (ob.val.length() - l)] = (ob.val[l-1] - 48)%10 + 48;
        p[p.length()-1 - (ob.val.length() - l) - 1] = (((ob.val[l-1] - 48)/10 == 0) ? '0' : '1');
    }

	res = sum(res, p);
    return CintN(res);
}

std::string CintN2::sum(const std::string &str1, const std::string &str2) {
	int i = str1.length()-1, j = str2.length()-1, p = 0; std::string res = "";
    while (i > -1 && j > -1) {
		res = std::to_string(((str1[i]-48) + (str2[j] - 48) + p)%10) + res;
		p = ((str1[i]-48) + (str2[j] - 48) + p)/10;
		--i; --j;
    }
    while (i > -1) {
		res = std::to_string((str1[i] - 48 + p)%10) + res;
		p = (str1[i] - 48 + p)/10;
		--i;
    }
    while (j > -1) {
        res = std::to_string((str2[j] - 48 + p)%10) + res;
        p = (str2[j] - 48 + p)/10;
        --j;
    }

    return res;
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

int Input(std::ifstream& in1, std::ifstream& in2, std::vector <CintN*> &v1, std::vector<CintN*> &v2, std::vector<CFabric*> &fab) {
    std::string value; std::vector<CintN*> tmp{};
    while (in1 >> value) {
        v1.push_back(fab[0] -> Create(value));
		tmp.push_back(fab[1]->Create(value));
    }
	v1.insert(v1.cend(), tmp.begin(), tmp.end());
	tmp.clear();
    
	while (in2 >> value) {
        v2.push_back(fab[0] -> Create(value));
		tmp.push_back(fab[1]->Create(value));
    }
	v2.insert(v2.cend(), tmp.begin(), tmp.end());
	tmp.clear();
    return 0;
}
