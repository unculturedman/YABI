#include <array>
#include <string>
#include <ncurses.h>
#include "debugDisplay.h"
#include "BFEngine/BFEngine.h"

using namespace bf;

void DebugDisplay::init(std::array<char, 3000>* ptr_to_memory) {
    memory_ptr = ptr_to_memory;
};

void DebugDisplay::end() {
    raw();
    endwin();
    return;
};

debug_command DebugDisplay::showDebugScreen(int starting_address, std::size_t current_code_position, std::string* ptr_to_code) {
    debug_command command;
    current_address = starting_address;
    current_position = current_code_position;
    code_ptr = ptr_to_code;

    initscr();
    noecho();
    curs_set(0);
    printw("Hello YABI!");
    refresh();

    do {
        command = handleInput();
        refresh();
    }
    while (command == NOOP);
    end();
    return command;
};

debug_command DebugDisplay::handleInput() {
    switch(getch()) {
        case 27:
            //27 is returned both for ALT and ESC keys. If no other key is pressed at the moment - assume ESC.
            nodelay(stdscr, 1);
            if (getch() == -1) {
                return QUIT;
            }
            nodelay(stdscr, 0) ;
            return NOOP;
        case KEY_ENTER:
            return CONTINUE;
    }
    return NOOP;
};
