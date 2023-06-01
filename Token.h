#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TokenType.h"

class Token {
public:
    Token(TokenType type, std::string value);

    TokenType getType() const;
    std::string getValue() const;
    std::string getTypeString() const;
    std::string value;
    TokenType type;
};

#endif
