#include <stdexcept>
#include <iostream>
#include <locale>
#include <codecvt>
#include "Lexer.h"
#include "Token.h"

Lexer::Lexer(std::string s) : source(std::move(s)), position(0),counter(0) {}

size_t Lexer::getPosition() const { return position; }

void Lexer::setPosition(size_t pos) {
    position = pos;
}

Token Lexer::getNextToken() {
  //  auto start = high_resolution_clock::now();

    // Skip whitespace
    skipWhitespace();

    // If we're at the end of the input, return an END_OF_FILE token
    if (position >= source.length()) {
        return Token(TokenType::END_OF_FILE, "");
    }

    unsigned char current = source[position];
    if (current == '=') {
        position++;
        return Token(TokenType::EQUAL, "=");
    } else if (current == '{') {
        position++;
        return Token(TokenType::OPEN_BRACE, "{");
    } else if (current == '}') {
        position++;
        return Token(TokenType::CLOSE_BRACE, "}");
    } else if (Lexer::isString(current)) {
        return getIdentifierToken();
    }
//    auto end = high_resolution_clock::now();
//    auto secs = std::chrono::duration_cast<microseconds>(end - start);
//    counter += secs.count();
//    std::cout<<counter<<std::endl;

    // Unrecognized character, throw an error
    throw std::runtime_error("Unrecognized character: " + std::to_string(current));
}


void Lexer::skipWhitespace() {
    while (position < source.length() && std::isspace(source[position])) {
        position++;
    }
}

Token Lexer::getIdentifierToken() {
    size_t start = position;
    bool in_quotations = false;

    while (position < source.length() && Lexer::isString(source[position], in_quotations)) {
        if (source[position] == '"') {
            if (!in_quotations) {
                in_quotations = true;
            } else {
                in_quotations = false;
            }
        }

        position++;
    }
    std::string identifier = source.substr(start, position - start);
    if (identifier == "EU4txt") return Token(TokenType::HEADER, "");

    return Token(TokenType::IDENTIFIER, identifier);
}

bool Lexer::isString(unsigned char ch, bool in_quotations) {

    char underscore = '_';
    char space = ' ';
    char hyphen = '-';
    char dot = '.';
    char quotations = '"';
    bool isString =
            std::iswalnum(ch) || in_quotations || ch == underscore || ch == dot || ch == quotations || ch == hyphen;
    return isString;
}

