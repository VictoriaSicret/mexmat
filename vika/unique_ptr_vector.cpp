#include "unique_ptr_vector.h" 
Vect::Vect()
{
	len = 0;
	data = nullptr;	
}
Vect::Vect(int num)
{
	len = num;
	data = std::make_unique<int []>(len);
	for (int k = 0; k < len; ++k) data[k] = rand() % 1000;
	std::cout << "Constructor for " << *this << std::endl;
}
Vect::~Vect() 
{
	std::cout << "Destructor for " << *this << std::endl;
	//delete []data;
}
Vect Vect::operator+(const Vect &vect)
{
	Vect result(len);
	for (int k = 0; k < len; ++k) 
		result.data[k] = data[k] + vect.data[k];
	return result;
}
Vect::Vect(const Vect &vect) : Vect(vect.len)
{
	for (int k = 0; k < len; ++k) data[k] = vect.data[k];
	std::cout << "Copy constructor" << *this << std::endl;	
}
Vect& Vect::operator= (const Vect &vect)
{
	std::cout << "Assignment operator" << *this << std::endl;
	if (this == &vect) return *this;
	len = vect.len;
	data = std::make_unique<int[]>(len);
	for (int k = 0; k < len; ++k) data[k] = vect.data[k];
	return *this;
}
Vect::Vect(Vect &&vect) {
	std::cout << "Move constructor" << *this << std::endl;
	//for (int k = 0; k < len; ++k) data[k] = vect.data[k];
	len = vect.len;
	data = std::move(vect.data);
	//vect.data = nullptr;
		
}
Vect& Vect::operator= (Vect &&vect)
{
	std::cout << "Move assignment" << *this << std::endl;
	if (this == &vect) return *this;
	len = vect.len;
	data = std::move(vect.data);
	//vect.data = nullptr;
	return *this;
}
std::ostream& operator<<(std::ostream &out, const Vect& vect)
{
	out << "(";
	for (int k = 0; k < vect.len; ++k)
		out << vect.data[k] << ", ";
	out << ")" << std::endl;
	return out;
}
