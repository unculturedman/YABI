# Yet Another Brainfuck Interpreter

A basic bf interpreter to be written in c++, as a university project.

## Installation Usage
You build the program by running `build.sh` or `build_win.bat` respectively. The program uses only stdlib so far.

If you want to run a .bf file use `bf <filename>`.
If you want to run YABI in interpreter mode, where you can write your own code, use `bf`.
You enable debug mode with `-d` flag.

## Limits
The program will not work correctly for code longer than `size_t - 1` (4294967295) characters.

### TODO:
- [ ] Working bf engine
- [ ] Reading and parsing .bf files
- [ ] Live parser
- [ ] Debug command, enabled by `-d` flag - ncurses maybe?
- [ ] Variable memory size with `-m` flag maybe?
- [ ] `-h` flag for help?
