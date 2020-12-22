#/bin/bash
g++ -c main.cpp -o main.o -I "$PWD"
g++ -c BFEngine/BFEngine.cpp -o bfe.o -I "$PWD"
g++ -c display/debugDisplay.cpp -o dd.o -I "$PWD"
g++ -o bin/bf.exe main.o bfe.o dd.o -lncurses
rm -f main.o
rm -f bfe.o
rm -f dd.o
