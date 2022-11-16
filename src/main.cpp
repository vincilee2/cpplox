#include<iostream>

#include "src/InterpreterDriver/InterpreterDriver.h"

auto main(int argc, char const* argv[]) -> int {
    cpplox::InterpreterDriver interpreter;
    interpreter.runPrompt();
    return 0;
}