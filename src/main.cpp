#include<iostream>

#include "InterpreterDriver.h"

auto main(int argc, char const* argv[]) -> int {
    cpplox::InterpreterDriver interpreter;
    interpreter.runREPL();
    return 0;
}