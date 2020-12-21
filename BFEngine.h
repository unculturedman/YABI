#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

namespace bf {
    typedef std::pair<std::size_t, std::size_t> gotoPair;
    typedef std::vector<gotoPair> gotoVector;

    struct commandChain {
        bool loop;
        std::size_t position = 0;
        std::string command;

        commandChain(std::string cmd, bool isLoop) {
            command = cmd;
            loop = isLoop;
        }
    };

    class BFEngine {
        bool debugMode;
        int address = 0;
        size_t current_position = 0;
        std::array<char, 30000> memory = {0};
        
        gotoVector goto_vector = {};
        void increment() {
            memory[address]++;
        }
        void decrement() {
            memory[address]--;
        }
        void moveRight() {
            address++;
        }
        void moveLeft() {
            address--;
        }
        void putChar() {
            putchar(memory[address]);
        }
        void getChar() {
            memory[address]=getchar();
        }
        void openLoop() {
            auto corresponding_pair = std::find_if(goto_vector.begin(), goto_vector.end(), [this] (gotoPair& zip) {
                return zip.first == current_position;
            });

            if (corresponding_pair == goto_vector.end()) {
                std::stringstream error_message;
                error_message << "Invalid open loop call at " << current_position << ". This is probably an interpreter issue.";
                fatal(error_message.str());
            }

            if (!memory[address]) {
                goTo((*corresponding_pair).second - 1);
            }
        }
        void closeLoop() {
            auto corresponding_pair = std::find_if(goto_vector.begin(), goto_vector.end(), [this] (gotoPair& zip) {
                return zip.second == current_position;
            });   

            if (corresponding_pair == goto_vector.end()) {
                std::stringstream error_message;
                error_message << "Invalid close loop call at " << current_position << ". This is probably an interpreter issue.";
                fatal(error_message.str());
            }

            if (memory[address]) {
                goTo((*corresponding_pair).first - 1);
            }
        }
        void goTo(std::size_t position) {
            current_position = position;
        }
        void initDebugScreen() {
            return;
            //Not implemented (use ncurses?)
        }
        void parseLoops(std::string code) {
            std::size_t position = 0;
            
            std::for_each(code.begin(), code.end(), [&] (char const &command) {
                switch (command) {
                    case '[':
                        goto_vector.push_back(gotoPair(position, -1));
                        break;
                    case ']':
                        auto corresponding_pair = std::find_if(goto_vector.rbegin(), goto_vector.rend(), [&] (gotoPair& zip) {
                            return zip.second == -1;
                        });

                        if (corresponding_pair == goto_vector.rend()) {
                            std::stringstream error_message;
                            error_message << "Invalid ] found at position: " << position << ". Shutting down;";
                            fatal(error_message.str());
                            exit(1);
                            return;
                        }

                        (*corresponding_pair).second = position;

                        break;
                }
                position++;
            }); 

        }
        void fatal(std::string message) {
            std::cerr << message;
            exit(1);
        }

    public:
        BFEngine(bool debug = 0) {
            debugMode = debug;
        }

        void parseString(std::string code) {
            parseLoops(code);

            size_t max_position = code.length() - 1;
            current_position = 0;

            while (current_position <= max_position) {
                char command = code[current_position];
                switch (command) {
                    case '+':
                        increment();
                        break;
                    case '-':
                        decrement();
                        break;
                    case '>':
                        moveRight();
                        break;
                    case '<':
                        moveLeft();
                        break;
                    case ',':
                        getChar();
                        break;
                    case '.':
                        putChar();
                        break;
                    case '[':
                        openLoop();
                        break;
                    case ']':
                        closeLoop();
                        break;
                    case '*':
                        if (debugMode) {
                            initDebugScreen();
                        }
                }
                current_position++;
            }
        }
    };
}