g++ -c main.cpp -o main.o -I %~dp0
g++ -c BFEngine\BFEngine.cpp -o bfe.o -I %~dp0
g++ -c display\debugDisplay.cpp -o dd.o -I %~dp0 -I c:\MinGW\include\ncursesw 
g++ -o bin\bf.exe main.o bfe.o dd.o -static-libstdc++ -lncursesw
del main.o
del bfe.o
del dd.o
