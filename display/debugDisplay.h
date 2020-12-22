#pragma once
#include <array>
#include <string>
#include <BFEngine/BFEngine.h>

namespace bf {
    class DebugDisplay {
        private: 
            int current_address;
            std::size_t current_position;
            std::string* code_ptr;
            std::array<char, 30000>* memory_ptr;

            bool handleInput();
            void end();
            
        public:
            void init(std::array<char, 30000>*);
            void showDebugScreen(int, std::size_t, std::string*);
    };
}
