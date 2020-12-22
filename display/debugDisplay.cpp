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

void DebugDisplay::showDebugScreen(int starting_address, std::size_t current_code_position, std::string* ptr_to_code) {
    current_address = starting_address;
    current_position = current_code_position;
    code_ptr = ptr_to_code;

    initscr();
    noecho();
    curs_set(0);
    printw("Hello YABI!");
    refresh();
    while (handleInput()) {
        refresh();
    }
    end();
    return;
};

bool DebugDisplay::handleInput() {
    switch(getch()) {
        case 'q': 
            return 0;
    }
    return 1;
}
