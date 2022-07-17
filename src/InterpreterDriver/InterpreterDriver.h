#ifndef CPPLOX_INTERPRETERDRIVER_INTERPRETERDRIVER_H
#define CPPLOX_INTERPRETERDRIVER_INTERPRETERDRIVER_H
#pragma once
#include <string>
#include <vector>

namespace cpplox {
    struct InterpreterDriver {
        public:
            InterpreterDriver();
            void runREPL();
        private:
            void interpret(const std::string& source);
            //Evaluator::Evaluator evaluator;
            //std::vector<std::vector<AST::StmtPtrVariant>> lines;
    };
}
#endif