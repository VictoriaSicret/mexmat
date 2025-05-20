CC = gcc
CFLAGS = -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors -Wunused -Wuninitialized --param inline-unit-growth=1000000 --param max-inline-insns-single=10000000 --param large-function-growth=10000000 -fPIC 

CXX = g++
CXXFLAGS = -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wcast-align -Werror -Wunused -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format


compilation: BMPImage main
	$(CXX) $(CXXFLAGS) main.o lib_BMP.o lib_BMP_impl.o -o app

check: BMPImage test 
	$(CXX) $(CXXFLAGS) -fopenmp test.o lib_BMP.o -o test

test:
	$(CXX) $(CXXFLAGS) -c test.cpp

BMPImage:
	$(CXX) $(CXXFLAGS) -c -fopenmp lib_BMP.hpp lib_BMP.cpp

main:
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -rf *.o *.out
