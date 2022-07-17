# include "src/Scanner/Scanner.h"
# include <map>
# include "src/Types/Token.h"

namespace cpplox {
    using Types::Token;
    using Types::TokenType;
    using namespace std;

    namespace {
        auto isAlpha(char c) -> bool {
            return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
        }

        auto isDigit(char c) -> bool {return isdigit(c);}

        auto isAlphaNumeric(char c) -> bool {return isAlpha(c)|| isDigit(c);}

        auto ReservedOrIdentifier(const string& str) -> TokenType {
            static const map<string, TokenType> lookUpTable {
                {"var", TokenType::VAR},
            };
            auto iter = lookUpTable.find(str);
            if (iter == lookUpTable.end()) {
                return TokenType::IDENTIFIER;
            }
            return iter->second;
        }

        auto getLexeme(const string& source, size_t start, size_t end) -> string {
            return source.substr(start, end);
        }
    }

    Scanner::Scanner(const string& p_source)
    : source(p_source) {}

    void Scanner::addToken(TokenType t) {
        string lexeme = getLexeme(source, start, current - start);
        tokens.emplace_back(t, lexeme);
    }

    void Scanner::advance() { ++current; }

    auto Scanner::isAtEnd() -> bool { return current >= source.size(); }

    auto Scanner::peek() -> char {
        if (isAtEnd()) return '\0';
        return source[current];
    }

    auto Scanner::peekNext() -> char {
        if ((current + 1) >= source.size()) return '\0';
        return source[current + 1];
    }
    
    void Scanner::eatIdentifier() {
        while (isAlphaNumeric(peek())) advance();
    }

    void Scanner::eatNumber() {
        while (isDigit(peek())) advance();

        if (peek() == '.' && isDigit(peekNext())) {
            advance();
            while (isDigit(peek())) advance();
        }
    }

    void Scanner::tokenizeOne() {
        char c = peek();
        advance();
        switch (c) {
            case ' ':
            case '\t':
            case '\r': break;
            case '\n': ++line; break;
            default:
                if (isDigit(c)) {
                    eatNumber();
                    addToken(TokenType::NUMBER);
                } else if (isAlpha(c)) {
                    eatIdentifier();
                    const string identifier = getLexeme(source, start, current - start);
                    addToken(ReservedOrIdentifier(identifier));
                } else {
                    string message = "Unexpected character: ";
                    message.append(1, static_cast<char>(c));
                }
                break;
        }
    }

    auto Scanner::tokenize() -> vector<Token> {
        while (!isAtEnd()) {
            start = current;
            tokenizeOne();
        }
        tokens.emplace_back(TokenType::LOX_EOF, "");
        vector<Token> tokenVec;
        move(tokens.begin(), tokens.end(), back_inserter(tokenVec));
        return tokenVec;
    }
}