#ifndef CINTN
#define CINTN
#define N 10

#include <cstdlib>
#include <iostream>
#include <string>

class CintN {
	private:
		char val[N];
		CintN (char arr[N]);
		CintN (std::string val);
	public:
		CintN (int value);
		
		virtual ~CintN ();
		
		CintN(const CintN &v);
		
		bool operator > (const CintN &v) const;

		bool operator == (const CintN &v) const;

		CintN operator+ (const CintN &v) const;
		
		CintN operator- (const CintN &v) const;
		
		CintN& operator= (const CintN &v);
		
		virtual std::string print() const = 0;
        virtual void Show(void) = 0;
		
		CintN& generate(int n);
		
		friend CintN make(bool flag_d, bool &flag);

		friend std::ostream& operator<< (std::ostream& os, CintN ob);
};

class CintN1: public CintN {
    public:
    std::string file;
    CintN1(std::string str, int value): CintN(value), file(str) {}
    ~CintN1() {std::cout << "CintN1 destructor\n" << std::endl;}

    std::string print() const {
        char number[N+1]; int k = 1; bool flag = true;
        number[0] = "!";
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

    friend std::ostream& operator<< (std::ostream& os, CintN1 ob);

    void Show(void) {
        ifstream f(file, ios::app);
        f << print();
        f.close;
    }
};

class CintN2: public CintN {
    public:
    std::string file;
    CintN2(std::string, int value): CintN(value), file(str) {}
    ~CintN2() {std::cout << "CintN2 destructor\n" << std::endl;}

    std::string print() const {
        char number[N+1]; int k = 1; bool flag = true;
        number[0] = "?";
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

    friend std::ostream& operator<< (std::ostream& os, CintN2 ob);
};

#endif
