#ifndef C2J_LEXER_H
#define C2J_LEXER_H

#include <string>
#include "Token.h"
#include <chrono>
using namespace std::chrono;

class Lexer {
public:
    explicit Lexer(std::string s);

    Token getNextToken();

    size_t getPosition() const;

    void setPosition(size_t pos);

private:
    int counter;
    std::string source;
    size_t position;
    typedef std::chrono::duration<float> float_seconds;

    bool isString(unsigned char ch, bool in_quotations = false);

    void skipWhitespace();
    Token getIdentifierToken();
};

#endif
