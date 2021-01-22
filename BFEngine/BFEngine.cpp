#include "BFEngine.hpp"
#include "display/debugDisplay.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <vector>
#include <fstream>

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
    debug_command returned_command;
    if (display) {
        returned_command = display->showDebugScreen(address, current_position, code_ptr);
        if (returned_command == QUIT) {
            die();
        }
        return;
    }
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

void BFEngine::die(std::string message) {
    std::cout << message;
    exit(0);
}

void BFEngine::die() {
    exit(0);
}

int BFEngine::parseString(std::string code) {
    std::cout << '\n';
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

    return 0;
}

int BFEngine::parseFile(std::string filepath) {
    std::ifstream parsedFile(filepath);
    std::string code;
    if (parsedFile.is_open()) {
        parsedFile.seekg(0, std::ios::end);
        code.reserve(parsedFile.tellg());
        parsedFile.seekg(0, std::ios::beg);
        code.assign(std::istreambuf_iterator<char>(parsedFile), std::istreambuf_iterator<char>());
        parsedFile.close();
        return this->parseString(code);
    }
    std::cout << "File \"" << filepath << "\" not found.";
    return 1;
}
