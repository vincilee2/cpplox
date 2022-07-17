#ifndef TOKEN_TYPE_HPP
#define TOKEN_TYPE_HPP

#include<string>
#include<iostream>

namespace cpplox::Types {
    enum class TokenType {
        // Single-character tokens
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        COLON,
        COMMA,
        DOT,
        QUESTION,
        SEMICOLON,
        SLASH,
        STAR,

        // One or two character tokens
        BANG,
        BANG_EQUAL,
        EQUAL,
        EQUAL_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,

        // Literals
        IDENTIFIER,
        STRING,
        NUMBER,

        // Keywords
        AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
        PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    };

    class Token {
        public:
            Token(TokenType p_type, const char* p_lexeme); 
        private:
            const TokenType type;
            const std::string lexeme;
    };
}
#endif