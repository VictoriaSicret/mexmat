all: main

main: LIB.o 5.o interface.o main.o 
	g++ -o main LIB.o 5.o interface.o main.o
main.o: main.cpp
	g++ -c main.cpp
interface.o: interface.cpp interface.h
	g++ -c interface.cpp
5.o: 5.cpp 5.h
	g++ -c 5.cpp
LIB.o: LIB.cpp LIB.h
	g++ -c LIB.cpp

clean: 
	rm main main.o 5.o interface.o LIB.o
