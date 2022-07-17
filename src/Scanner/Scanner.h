#ifndef CPPLOX_SCANNER_SCANNER_H
#define CPPLOX_SCANNER_SCANNER_H
#pragma once

#include <list>
#include <string>
#include <vector>

#include "src/Types/Token.h"

namespace cpplox {
    using Types::Token;
    using Types::TokenType;

    class Scanner {
        public:
            Scanner(const std::string &p_source);
            auto tokenize() -> std::vector<Token>;
        private:
            auto isAtEnd() -> bool;
            void tokenizeOne();
            void advance();
            auto matchNext(char expected) -> bool;
            auto peek() -> char;
            auto peekNext() -> char;
            void eatNumber();
            void eatIdentifier();
            void addToken(TokenType t);

            const std::string &source;
            std::list<Token> tokens;
            size_t start = 0;
            size_t current = 0;
            int line = 1;
    };
}
#endif