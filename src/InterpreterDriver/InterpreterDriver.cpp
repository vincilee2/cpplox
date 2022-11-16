#include "InterpreterDriver.h"

#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>

#include "src/Types/Token.h"
#include "src/Scanner/Scanner.h"

namespace cpplox {
    using Types::TokenType;
    void InterpreterDriver::runPrompt() {
        std::string line;
        std::cout 
            << "Crafting Interpreter.\n"
            << std::endl;
        while (std::cout << "> " && std::getline(std::cin, line)) {
            this->interpret(line);
        }
        std::cout << std::endl << "# Goodbye!" << std::endl;
    }

    auto InterpreterDriver::runScript(const char* scriptFile) -> int {
        const auto source = ([&]() -> std::string {
            try {
                std::ifstream in(scriptFile, std::ios::in);
                in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                return std::string {
                    std::istreambuf_iterator<char>{in},
                    std::istreambuf_iterator<char>{}
                };
            } catch (std::exception& e) {
                std::cout << "Cannot open source file" << std::endl;
                return "";
            }
        })();

        this->interpret(source);
        
        return 0;
    }

    void InterpreterDriver::interpret(const std::string& source) {
        Scanner scanner(source);
        auto tokens = scanner.tokenize();
        for (auto token:tokens) {
            std::cout << token.toString() << std::endl;
        }
        return;
    }

    InterpreterDriver::InterpreterDriver() {
        
    }
}