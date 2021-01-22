#include <array>
#include <string>
#include <ncurses.h>
#include <iostream>
#include "debugDisplay.hpp"
#include "BFEngine/BFEngine.hpp"

using namespace bf;

void DebugDisplay::init(std::array<char, 3000>* ptr_to_memory) {
    memory_ptr = ptr_to_memory;
};

void DebugDisplay::end() {
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
    getmaxyx(stdscr, scr_y, scr_x);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_RED);
    }

    do {
        erase();
        displayMemory();
        refresh();
        command = handleInput();
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
            nodelay(stdscr, 0);
            return NOOP;
        case '\n':
            return CONTINUE;
        case 0:
            //For arrow keys, there are 2 values returned, of which first one is 0.
            nodelay(stdscr, 1);
            switch(getch()) {
                case 72:
                    current_address--;
                    break;
                case 80:
                    current_address++;
            }
            nodelay(stdscr, 0);
    }
    return NOOP;
};

void DebugDisplay::displayMemory() {
    int starting_addr = current_address - (scr_y / 2);
    for (int i = 0; i < scr_y; i++) {
        if (starting_addr + i >= 0) {
            if (current_address == starting_addr + i && has_colors()) {
                attron(COLOR_PAIR(1));
                mvprintw(i, 0, "        "); //TODO: This is ugly, think off something else to color in rows pls;
                printMemoryLine(i, starting_addr);
                attroff(COLOR_PAIR(1));
            } else {
                printMemoryLine(i, starting_addr);
            }
        } else {
            if (current_address == starting_addr + i && has_colors()) {
                attron(COLOR_PAIR(1));
                mvprintw(i, 0, "        ");
                attroff(COLOR_PAIR(1));
            }
        }
    }
}

void DebugDisplay::printMemoryLine(int row, int starting_addr) {
    mvprintw(row, 0, "%i:", starting_addr + row + 1);
    mvprintw(row, 5, "%i", (*memory_ptr)[starting_addr + row]);
}

void DebugDisplay::displayCode() {
    
}
