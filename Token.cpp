#include "Token.h"

Token::Token(TokenType type, std::string value) : type(type), value(std::move(value)) {}

TokenType Token::getType() const {
    return type;
}
//For debug purposes
std::string Token::getTypeString() const {
    switch (type) {
        case TokenType::EQUAL:
            return "EQUAL";
        case TokenType::NUMBER:
            return "NUMBER";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::OPEN_BRACE:
            return "OPEN_BRACE";
        case TokenType::CLOSE_BRACE:
            return "CLOSE_BRACE";
        case TokenType::END_OF_FILE:
            return "END_OF_FILE";
        case TokenType::HEADER:
            return "HEADER";
    }
    return "UNDEFINED";
}
std::string Token::getValue() const {
    return value;
}
