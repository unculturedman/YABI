#pragma once
#include <array>
#include <string>
#include <BFEngine/BFEngine.h>

namespace bf {
    enum debug_command {NOOP, CONTINUE, QUIT};

    class DebugDisplay {
        private: 
            int current_address;
            std::size_t current_position;
            std::string* code_ptr;
            std::array<char, 3000>* memory_ptr;

            debug_command handleInput();
            void end();
            
        public:
            void init(std::array<char, 3000>*);
            debug_command showDebugScreen(int, std::size_t, std::string*);
    };
}
