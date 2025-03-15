#ifndef CINTN
#define CINTN

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class CFabric;

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
	CintN operator+ () const;
	CintN operator- () const;

	bool operator== (const CintN& ob) const;
        bool operator!= (const CintN& ob) const;
	bool operator< (const CintN& ob) const;
        bool operator<= (const CintN& ob) const;
        bool operator> (const CintN& ob) const;
        bool operator>= (const CintN& ob) const;

        virtual std::string print() const {
		return val;
	}

        virtual void Show(void) {
		std::cout << print() << std::endl;
	}

        friend std::ostream& operator<< (std::ostream& os, const CintN& ob);
};

class CintN1: public CintN {
    public:
    std::string file;
    CintN1(std::string f, std::string value): CintN(value), file(f) {}
    ~CintN1() {std::cout << "CintN1 destructor\n" << std::endl;}

    std::string print() const {
        std::string res = "!"; res += val;
        return res;
    }

    friend std::ostream& operator<< (std::ostream& os, const CintN1& ob);

    void Show(void) {
        std::ofstream f(file.c_str(), std::ios::app);
        f << print() << "\n";
        f.close();
    }
};

class CintN2: public CintN {
    public:
    std::string file;
    CintN2(std::string f, std::string value): CintN(value), file(f) {}
    ~CintN2() {std::cout << "CintN2 destructor\n" << std::endl;}

    std::string print() const {
        std::string res = "?"; res += val; 
        return res;
    }

    friend std::ostream& operator<< (std::ostream& os, const CintN2& ob);

    void Show(void) {
        std::ofstream f(file.c_str(), std::ios::app);
        f << print() << "\n";
        f.close();
    }
};

class CFabric
{
	public:
	virtual CintN* Create(std::string, std::string) = 0;
	virtual ~CFabric() {}; 
};

class CFabric1 : public CFabric
{
	public:
	CintN* Create(std::string file, std::string value) override {return new CintN1(file, value);}  
};

class CFabric2 : public CFabric
{
	public:
 	CintN* Create(std::string file, std::string value) override{return new CintN2(file, value);}     
};

int Input(std::ifstream&, std::vector <CintN*>&, std::vector <CFabric*>&);
#endif
