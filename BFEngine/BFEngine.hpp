#pragma once
#include <array>
#include <vector>
#include <string>
#include <utility>
#include "display/debugDisplay.hpp"

namespace bf {
    typedef std::pair<std::size_t, std::size_t> gotoPair;
    typedef std::vector<gotoPair> gotoVector;

    class DebugDisplay;

    class BFEngine {
        private: 
            bool debugMode;
            int address = 0;
            size_t current_position = 0;
            std::array<char, 3000> memory = {0};
            gotoVector goto_vector = {};
            DebugDisplay* display;
        
            void increment();
            void decrement();
            void moveRight();
            void moveLeft();
            void putChar();
            void getChar();
            void openLoop();
            void closeLoop();
            void goTo(std::size_t);
            void enableDebug();
            void initDebugScreen(std::string*);
            void parseLoops(std::string);
            void fatal(std::string);
            void die();
            void die(std::string);

        public:
            BFEngine();
            BFEngine(bool);
            int parseString(std::string);
            int parseFile(std::string);
    };

}