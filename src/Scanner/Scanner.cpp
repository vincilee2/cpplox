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
                {"and", TokenType::AND},       {"class", TokenType::CLASS},
                {"else", TokenType::ELSE},     {"false", TokenType::FALSE},
                {"fun", TokenType::FUN},       {"for", TokenType::FOR},
                {"if", TokenType::IF},         {"nil", TokenType::NIL},
                {"or", TokenType::OR},         {"print", TokenType::PRINT},
                {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
                {"this", TokenType::THIS},     {"true", TokenType::TRUE},
                {"var", TokenType::VAR},       {"while", TokenType::WHILE}};
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
        tokens.emplace_back(t, lexeme, lexeme, line);
    }

    void Scanner::advance() { ++current; }

    auto Scanner::matchNext(char expetecd) -> bool {
        bool nextMatches = (peek() == expetecd);
        if (nextMatches) advance();
        return nextMatches;
    }
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
            case '(': addToken(TokenType::LEFT_PAREN); break;
            case ')': addToken(TokenType::RIGHT_PAREN); break;
            case '{': addToken(TokenType::LEFT_BRACE); break;
            case '}': addToken(TokenType::RIGHT_BRACE); break;
            case ',': addToken(TokenType::COMMA); break;
            case '.': addToken(TokenType::DOT); break;
            case ';': addToken(TokenType::SEMICOLON); break;
            case '*': addToken(TokenType::STAR); break; 
            case '!': 
                addToken(matchNext('=') ? TokenType::BANG_EQUAL : TokenType::BANG); 
                break;
            case '=':
                addToken(matchNext('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
                break;
            case '>':
                addToken(matchNext('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
                break;
            case '<':
                addToken(matchNext('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
                break;
            case '-':
                addToken(matchNext('-') ? TokenType::MINUS_MINUS : TokenType::MINUS);
                break;
            case '+':
                addToken(matchNext('+') ? TokenType::PLUS_PLUS : TokenType::PLUS);
                break;
            // todo support comments

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
                    message.append(line, static_cast<char>(c));
                    std::cout << message << std::endl;
                }
                break;
        }
    }

    auto Scanner::tokenize() -> vector<Token> {
        while (!isAtEnd()) {
            start = current;
            tokenizeOne();
        }
        tokens.emplace_back(TokenType::LOX_EOF, "", "", line);
        vector<Token> tokenVec;
        move(tokens.begin(), tokens.end(), back_inserter(tokenVec));
        return tokenVec;
    }
}