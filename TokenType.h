// TokenType.h

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <array>
#include <string>

enum class TokenType {
    EQUAL, NUMBER, IDENTIFIER, OPEN_BRACE, CLOSE_BRACE, END_OF_FILE,HEADER
};
std::string getTokenType(TokenType t);
#endif
