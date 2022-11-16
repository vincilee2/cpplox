#include "Token.h"
#include <map>
#include <string>
namespace cpplox::Types {

    namespace{
        auto TokenTypeString(const TokenType value) -> const std::string& {
            static const std::map<TokenType, std::string> lookupTable {
            {TokenType::EQUAL, "EQUAL"},
            {TokenType::VAR, "VAR"},
            {TokenType::NUMBER, "NUMBER"},
            };
            return lookupTable.find(value)->second;
        };
    }

    Token::Token(TokenType p_type, std::string p_lexeme)
        : type(p_type),
        lexeme(p_lexeme) {}
    
    Token::Token(TokenType p_type, std::string p_lexeme, const char* p_literal, int p_line)
        : type(p_type),
        lexeme(p_lexeme),
        literal(p_literal),
        line(p_line) {}

    auto Token::toString() const -> std::string {
        std::string result
            = std::to_string(line) + " " + TokenTypeString(type) + " " + lexeme + " ";
        return result;
    }
}