#pragma once
#include <array>
#include <string>
#include <BFEngine/BFEngine.hpp>

namespace bf {
    enum debug_command {NOOP, CONTINUE, QUIT};

    class DebugDisplay {
        private: 
            int current_address;
            int scr_x;
            int scr_y;
            std::size_t current_position;
            std::string* code_ptr;
            std::array<char, 3000>* memory_ptr;

            debug_command handleInput();
            void displayMemory();
            void printMemoryLine(int, int);
            void displayCode();
            void end();
            
        public:
            void init(std::array<char, 3000>*);
            debug_command showDebugScreen(int, std::size_t, std::string*);
    };
}
