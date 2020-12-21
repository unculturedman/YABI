#include "BFEngine.h"
#include <iostream>

using namespace std;
using namespace bf;

int main(int argc, char *argv[]) {
  BFEngine engine = BFEngine();
  //Testing - a simple hello world.
  engine.parseString("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.");
  return 0;
}