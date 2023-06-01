#include "Parser.h"

Parser::Parser(Lexer &l) : lexer(l), currentToken(lexer.getNextToken()) {}
std::unique_ptr<Node> Parser::parse() {
    return parseObject();
}
std::unique_ptr<ObjectNode> Parser::parseMap() {
    std::unique_ptr<ObjectNode> object = std::make_unique<ObjectNode>();
    std::unique_ptr<Node> value;
    std::string key = "key";
    while (currentToken.type != TokenType::CLOSE_BRACE && currentToken.type != TokenType::END_OF_FILE) {
        if (currentToken.type == TokenType::IDENTIFIER) {
            key = currentToken.value;
        }
        getNextToken();
        expect(TokenType::EQUAL);
        if (currentToken.type == TokenType::IDENTIFIER) {
            value = std::make_unique<ValueNode>(currentToken.value);
        } else if (currentToken.type == TokenType::OPEN_BRACE) {
            value = parseObject();
        } else {
            throw std::runtime_error("Expected a value, got " + currentToken.value);
        }
        object->children.emplace_back(key, std::move(value));
        getNextToken();
    }
    return object;
};
//Array is a {} object that doesn't contain any key-value pairs. For instance: color = { 1 1 1 }
std::unique_ptr<Node> Parser::parseArray() {
    std::unique_ptr<ArrayNode> array = std::make_unique<ArrayNode>();
    while (currentToken.type == TokenType::IDENTIFIER) {
        std::unique_ptr<ValueNode> value = std::make_unique<ValueNode>(currentToken.value);
        if (currentToken.type == TokenType::OPEN_BRACE) {
            getNextToken();
        }
        expect(TokenType::IDENTIFIER);
        array->values.push_back(std::move(value));
    }
    return array;
}
//Object is anything between curly {} braces. Later on we distinguish between an array { a, b, c} and map {key = value}
std::unique_ptr<Node> Parser::parseObject() {
    expect(TokenType::OPEN_BRACE);

    //Looking up 2 tokens ahead allows us to determine what type of object we are dealing with.
    size_t current_position = lexer.getPosition();
    Token lookup = lexer.getNextToken();
    Token lookup_second = lexer.getNextToken();
    lexer.setPosition(current_position);


    std::unique_ptr<ObjectNode> obj = std::make_unique<ObjectNode>();
    if (currentToken.type == TokenType::IDENTIFIER && lookup.type == TokenType::EQUAL) {
        //Normal map, ie. { a = b }
        obj = parseMap();
        return obj;
    } else if (currentToken.type == TokenType::OPEN_BRACE) {
        //Nested array of objects, ie. { { a = b } { b = a } }
        auto node = std::make_unique<ArrayNode>();
        node->values.push_back(parseObject());
        getNextToken();
        while (currentToken.type == TokenType::OPEN_BRACE) {
            node->values.push_back(parseObject());
            getNextToken();
        }
        return node;
    } else {
        //Array, ie. { 0 1 2 3 }
        std::unique_ptr<Node> array = std::make_unique<ArrayNode>();
        array = parseArray();
        return array;
    }
}

void Parser::expect(TokenType type) {
    if (currentToken.type == type) {
        getNextToken();
    } else {
        throw std::runtime_error("Expected " + getTokenType(type) + ", got " +
                                 getTokenType(currentToken.type) + " at token: " + currentToken.value);
    }
}

void Parser::getNextToken() {
    currentToken = lexer.getNextToken();
}