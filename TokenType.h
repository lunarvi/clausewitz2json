#ifndef C2J_TOKEN_TYPE_H
#define C2J_TOKEN_TYPE_H

#include <array>
#include <string>

enum class TokenType {
    EQUAL, NUMBER, IDENTIFIER, OPEN_BRACE, CLOSE_BRACE, END_OF_FILE,HEADER
};
std::string getTokenType(TokenType t);
#endif
