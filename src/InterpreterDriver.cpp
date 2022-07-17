#include "InterpreterDriver.h"

#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>

#include "TokenType.h"

namespace cpplox {
    using Types::TokenType;

    void InterpreterDriver::runREPL() {
        std::string line;
        std::cout 
            << "Crafting Interpreter.\n"
            << std::endl;
        while (std::cout << "> " && std::getline(std::cin, line)) {
            std::cout << line;
        }
        std::cout << std::endl << "# Goodbye!" << std::endl;
    }

    void InterpreterDriver::interpret(const std::string& source) {
        return;
    }

    InterpreterDriver::InterpreterDriver() {
        
    }
}