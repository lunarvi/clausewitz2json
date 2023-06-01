#include "TokenType.h"

std::string getTokenType(TokenType t) {
    switch (t) {
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