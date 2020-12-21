g++ -c main.cpp -o main.o
g++ -c BFEngine\BFEngine.cpp -o bfe.o
g++ -o bin\bf.exe main.o bfe.o -static-libstdc++
del main.o
del bfe.o
