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

    Token::Token(TokenType p_type, const char* p_lexeme)
        : type(p_type),
        lexeme(p_lexeme) {TokenTypeString(TokenType::AND);}
    
}