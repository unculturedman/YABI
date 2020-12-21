#/bin/bash
g++ -c main.cpp -o main.o
g++ -c BFEngine/BFEngine.cpp -o bfe.o
g++ -o bin/bf.exe main.o bfe.o
rm -f main.o
rm -f bfe.o
