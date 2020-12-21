#pragma once
#include <array>
#include <vector>
#include <string>
#include <utility>

namespace bf {
    typedef std::pair<std::size_t, std::size_t> gotoPair;
    typedef std::vector<gotoPair> gotoVector;

    class BFEngine {
        private: 
            bool debugMode;
            int address = 0;
            size_t current_position = 0;
            std::array<char, 30000> memory = {0};
            gotoVector goto_vector = {};
        
            void increment();
            void decrement();
            void moveRight();
            void moveLeft();
            void putChar();
            void getChar();
            void openLoop();
            void closeLoop();
            void goTo(std::size_t);
            void initDebugScreen();
            void parseLoops(std::string);
            void fatal(std::string);

        public:
            BFEngine(bool);
            void parseString(std::string);
    };

}