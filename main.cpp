#include "BFEngine/BFEngine.hpp"
#include <iostream>

using namespace std;
using namespace bf;

int main(int argc, char *argv[]) {
  BFEngine engine = BFEngine(1);
  //Testing - a simple hello world.
  engine.parseString("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+*++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.");
  return 0;
}