compilation: BMPImage main
	g++ main.o lib_BMP.o lib_BMP_impl.o -o app

check: test
	g++ -fopenmp test.o lib_BMP.o lib_BMP_impl.o -o test

test:
	g++ -c -std=c++20 -fmodules-ts test.cpp

BMPImage:
	g++ -c -std=c++20 -fmodules-ts lib_BMP.cxx
	g++ -c -std=c++20 -fmodules-ts -fopenmp lib_BMP_impl.cxx

main:
	g++ -c -std=c++20 -fmodules-ts  main.cpp

clean:
	rm -rf *.o *.out
