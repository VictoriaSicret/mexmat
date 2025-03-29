#ifndef CINTN
#define CINTN

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <omp.h>

class CFabric;

class ExceptCintN: public std::exception {
	private:
	std::string message;
	
	public:
	ExceptCintN(const std::string& message): message(message) {}
	const char* what() const noexcept override {return message.c_str();}	
};

class CintN {
	public:
	std::string val;

    CintN (std::string val);
    CintN (int value = 0): val(std::to_string(value)) {}
    virtual ~CintN () {}

    CintN(const CintN &v): val(v.val) {}
    CintN& operator= (const CintN &v);

	CintN operator+ (const CintN& ob) const;
	CintN operator- (const CintN& ob) const;
	CintN& operator+= (const CintN& ob);
	CintN operator+ () const;
	CintN operator- () const;
	virtual CintN operator* (const CintN& ob) const;

	bool operator== (const CintN& ob) const;
    bool operator!= (const CintN& ob) const;
	bool operator< (const CintN& ob) const;
    bool operator<= (const CintN& ob) const;
    bool operator> (const CintN& ob) const;
    bool operator>= (const CintN& ob) const;

    std::string print() const {return val;}
	void Show(void) {std::ofstream f("res.txt", std::ios::app); f << print() +" "; f.close();}

    friend std::ostream& operator<< (std::ostream& os, const CintN& ob);
};

class CintN1: public CintN {
    public:
	CintN1(const CintN &ob): CintN(ob) {}
    CintN1(std::string value): CintN(value) {}
	CintN1(int value = 0): CintN(value) {}
    ~CintN1() {}

    friend std::ostream& operator<< (std::ostream& os, const CintN1& ob);
};

class CintN2: public CintN {
    public:
    CintN2(std::string value): CintN(value) {}
	CintN2(const CintN &ob): CintN(ob) {}
	CintN2(int value = 0): CintN(value) {}
	CintN operator* (const CintN& ob) const override;

    ~CintN2() {}

    friend std::ostream& operator<< (std::ostream& os, const CintN2& ob);
};

class CFabric
{
	public:
	virtual CintN* Create(std::string) = 0;
	virtual ~CFabric() {}; 
};

class CFabric1 : public CFabric
{
	public:
	CintN* Create(std::string value) override {return new CintN1(value);}  
};

class CFabric2 : public CFabric
{
	public:
 	CintN* Create(std::string value) override{return new CintN2(value);}     
};

int Input(int, std::ifstream&, std::ifstream&, std::vector <CintN*>&, std::vector<CintN*>&, std::vector <CFabric*>&);

std::string genString(size_t n);
void gen(std::ofstream& os, size_t n, size_t k);
#endif
