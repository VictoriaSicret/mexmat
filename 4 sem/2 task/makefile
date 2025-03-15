all: res

clean:
	rm -rf *.o *.out

1.o: 1.cpp
	g++ -c -lm  1.cpp

main.o: main.cpp
	g++ -c -lm  main.cpp

res: 1.o main.o
	g++ main.o 1.o
