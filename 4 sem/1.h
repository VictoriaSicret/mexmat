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
        char number[N+2]; int k = 1; bool flag = true;
        number[0] = '!';
        for (int i = N; i >= 0; i--) {
            if (flag) {
                if (val[i] != 0) flag = false;
                else continue;
            }
            number[k] = val[i] + 48;
            k++;
        }
        for (int i = k; i < N+1; i++) number[i] = 0;
        std::string res(number);
        if(res.empty()) res = "!0";
        return res;
    }

    friend std::ostream& operator<< (std::ostream& os, const CintN1& ob);

    void Show(void) {
        std::ofstream f(file.c_str(), std::ios::app);
        f << print();
        f.close();
    }
};

class CintN2: public CintN {
    public:
    std::string file;
    CintN2(std::string f, std::string value): CintN(value), file(f) {}
    ~CintN2() {std::cout << "CintN2 destructor\n" << std::endl;}

    std::string print() const {
        char number[N+1]; int k = 1; bool flag = true;
        number[0] = '?';
        for (int i = N; i >= 0; i--) {
            if (flag) {
                if (val[i] != 0) flag = false;
                else continue;
            }
            number[k] = val[i] + 48;
            k++;
        }
        for (int i = k; i < N+1; i++) number[i] = 0;
        std::string res(number);
        if(res.empty()) res = "?0";
        return res;
    }

    friend std::ostream& operator<< (std::ostream& os, const CintN2& ob);

    void Show(void) {
        std::ofstream f(file.c_str(), std::ios::app);
        f << print();
        f.close();
    }
};

int Input(std::ifstream&, std::vector <CintN*>&);
#endif
