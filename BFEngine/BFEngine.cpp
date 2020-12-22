#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <vector>
#include "BFEngine.h"
#include "display/debugDisplay.h"

using namespace bf;

BFEngine::BFEngine(bool debug = 0) {
    debugMode = debug;
    if (debug) {
        enableDebug();
    }
}

void BFEngine::increment() {
    memory[address]++;
}

void BFEngine::decrement() {
    memory[address]--;
}

void BFEngine::moveRight() {
    address++;
}

void BFEngine::moveLeft() {
    address--;
}

void BFEngine::putChar() {
    putchar(memory[address]);
}

void BFEngine::getChar() {
    memory[address]=getchar();
}

void BFEngine::openLoop() {
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

void BFEngine::closeLoop() {
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

void BFEngine::initDebugScreen(std::string* code_ptr) {
    if (display) {
        display->showDebugScreen(address, current_position, code_ptr);
        return;
    }
    std::stringstream error_message;
    error_message << "Invalid initDEbugScreen call at " << current_position << ". This is probably an interpreter issue.";
    fatal(error_message.str());
}

void BFEngine::enableDebug() {
    DebugDisplay d = DebugDisplay();
    display = &d;
    display->init(&memory);
    return;
}

void BFEngine::goTo(std::size_t position) {
    current_position = position;
}

void BFEngine::parseLoops(std::string code) {
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

void BFEngine::fatal(std::string message) {
    std::cerr << message;
    exit(1);
}

void BFEngine::parseString(std::string code) {
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
                    initDebugScreen(&code);
                }
        }
        current_position++;
    }
}
