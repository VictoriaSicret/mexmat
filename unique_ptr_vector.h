#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <ostream>
#include <memory>
class Vect
{
private:
	int len;
	std::unique_ptr<int []> data;
public:
	// default constructor
	Vect();
	// constructor
	Vect(int num);
	// destructor
	~Vect();
	Vect operator+(const Vect &vect);
	Vect(const Vect &b);
	Vect& operator= (const Vect &vect);
	Vect(Vect &&vect);
	Vect& operator= (Vect &&vect);
	// output operator
	friend std::ostream& operator<<(std::ostream &out, const Vect& vect);
};




#endif