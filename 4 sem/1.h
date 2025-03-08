#ifndef CINTN
#define CINTN
#define N 10

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class CintN {
    private:
        CintN (char arr[N+1]);
    public:
        char val[N+1];

        CintN (std::string val);
        CintN (int value);
        virtual ~CintN () {};

        CintN(const CintN &v);
        CintN& operator= (const CintN &v);

        virtual std::string print() const = 0;
        virtual void Show(void) = 0;

        friend std::ostream& operator<< (std::ostream& os, const CintN& ob);
};

class CintN1: public CintN {
    public:
    std::string file;
    CintN1(std::string f, std::string value): CintN(value), file(f) {}
    ~CintN1() {std::cout << "CintN1 destructor\n" << std::endl;}

    std::string print() const {
        char number[N+2];
        number[0] = '!';
        for (int i = 1; i < N+2; ++i) number[i] = val[i-1];
        std::string res(number);
        if(res.empty()) res = "!0";
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
        char number[N+2];
        number[0] = '?';
        for (int i = 1; i < N+2; ++i) number[i] = val[i-1];
        std::string res(number);
        if(res.empty()) res = "!0";
        return res;
    }

    friend std::ostream& operator<< (std::ostream& os, const CintN2& ob);

    void Show(void) {
        std::ofstream f(file.c_str(), std::ios::app);
        f << print() << "\n";
        f.close();
    }
};

int Input(std::ifstream&, std::vector <CintN*>&);
#endif
