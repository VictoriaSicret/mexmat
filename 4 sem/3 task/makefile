all: res

clean:
	rm -rf *.o *.out

3.o: 3.cpp
	g++ -c -fopenmp  3.cpp

main.o: main.cpp
	g++ -c -fopenmp  main.cpp

res: 3.o main.o
	g++ -fopenmp main.o 3.o
