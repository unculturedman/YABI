#include "BFEngine/BFEngine.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace bf;

int main(int argc, char *argv[]) {
  std::vector<std::string> args(argv, argv + argc);
  bool debug_mode = 0;
  bool inline_mode = 0;
  std::string filepath;

  int counter = 0;
  for_each(args.begin()+1, args.end(), [&] (std::string arg) {
    if (arg == "-d") {
      debug_mode = 1;
    } else if (arg == "-i") {
      inline_mode = 1;
    } else if (filepath.empty()) {
      filepath = arg;
    }
    counter++;
  });

  BFEngine engine = BFEngine(debug_mode);

  if (!filepath.empty()) {
    if (inline_mode) {
      return engine.parseString(filepath);
    }
    return engine.parseFile(filepath);
  }
  //Testing - a simple hello world.
  //engine.parseString("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+*++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.");
  std::cout << "No file was specified.";
  return 1;
}