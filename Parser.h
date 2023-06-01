#ifndef C2J_PARSER_H
#define C2J_PARSER_H

#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

#include "TokenType.h"
#include "Node.h"
#include "Lexer.h"

class Parser {
public:
    Parser(Lexer &l);

    std::unique_ptr<Node> parse();

private:
    Lexer &lexer;
    Token currentToken;

    std::unique_ptr<ObjectNode> parseMap();

    std::unique_ptr<Node> parseArray();

    std::unique_ptr<Node> parseObject();

    void expect(TokenType type);

    void getNextToken();
};

#endif
