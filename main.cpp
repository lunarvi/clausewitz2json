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
    Parser(Lexer &l) : lexer(l), currentToken(lexer.getNextToken()) {}

    std::unique_ptr<Node> parse() {
        return parseObject();
    }

private:
    Lexer &lexer;
    Token currentToken;
    bool lookupIfArray(){
        size_t current_position = lexer.getPosition();
        bool is_array = true;
        while (currentToken.type != TokenType::CLOSE_BRACE) {
            getNextToken();
            if (currentToken.type == TokenType::EQUAL) {
                is_array = false;
                break;
            }
        }
        lexer.setPosition(current_position);
        return is_array;
    }
    std::unique_ptr<ObjectNode> parseMap() {
        std::unique_ptr<ObjectNode> object = std::make_unique<ObjectNode>();
        std::unique_ptr<Node> value;
        std::string key = "key";
        while (currentToken.type != TokenType::CLOSE_BRACE && currentToken.type != TokenType::END_OF_FILE) {
            if(currentToken.type == TokenType::IDENTIFIER) {
                key = currentToken.value;
            }
            getNextToken();
            expect(TokenType::EQUAL);
            if (currentToken.type == TokenType::IDENTIFIER) {
                value = std::make_unique<ValueNode>(currentToken.value);
            }else if (currentToken.type == TokenType::OPEN_BRACE){
                value = parseObject();
            } else {
                throw std::runtime_error("Expected a value, got " + currentToken.value);
            }
            object->children.emplace_back(key, std::move(value));
            getNextToken();
        }
        return object;
    };
    //Object is anything between curly {} braces. Later on we distinguish between an array { a, b, c} and map {key = value}
    std::unique_ptr<Node> parseObject() {
        // Expect an opening brace
        expect(TokenType::OPEN_BRACE);
        size_t current_position = lexer.getPosition();
        Token lookup = lexer.getNextToken();
        Token lookup_second = lexer.getNextToken();
        lexer.setPosition(current_position);
        std::unique_ptr<ObjectNode> obj = std::make_unique<ObjectNode>();
        if(currentToken.type == TokenType::IDENTIFIER && lookup.type == TokenType::EQUAL){
            //Normal map, ie. { a = b }
            obj = parseMap();
            return obj;
        }else if(currentToken.type == TokenType::OPEN_BRACE){
            //Nested array of objects, ie. { { a = b } { b = a } }
            auto node = std::make_unique<ArrayNode>();
            node->values.push_back(parseObject());
            getNextToken();
            while (currentToken.type == TokenType::OPEN_BRACE) {
                node->values.push_back(parseObject());
                getNextToken();
            }
            return node;
            std::cout << "Nested array!" << std::endl;
        }else{
            //Array, ie. { 0 1 2 3 }
            std::unique_ptr<Node> array = std::make_unique<ArrayNode>();
            array = parseArray();
            return array;
        }
    }

    //Array is a {} object that doesn't contain any key-value pairs. For instance: color = { 1 1 1 }
    std::unique_ptr<Node> parseArray() {
        std::unique_ptr<ArrayNode> array = std::make_unique<ArrayNode>();

        while (currentToken.type == TokenType::IDENTIFIER) {
            // Expect a number
            std::unique_ptr<ValueNode> value = std::make_unique<ValueNode>(currentToken.value);
            if(currentToken.type == TokenType::OPEN_BRACE) {
                getNextToken();
            }
                expect(TokenType::IDENTIFIER);
            array->values.push_back(std::move(value));
        }
        // Expect a closing brace
        //expect(TokenType::CLOSE_BRACE);
        return array;
    }

    void expect(TokenType type) {
        if (currentToken.type == type) {
            getNextToken();
        } else {
            throw std::runtime_error("Expected " + getTokenType(type) + ", got " +
                                     getTokenType(currentToken.type) + " at token: " + currentToken.value);
        }
    }

    void getNextToken(bool debug = false) {
     //   debug = true;
        if(debug){
         //   std::cout<<"Before:"<<getTokenType(currentToken.type)+" "+currentToken.value<<std::endl;
        }
        currentToken = lexer.getNextToken();
        if(debug){
            std::cout<<"After:"<<getTokenType(currentToken.type)+" "+currentToken.value<<std::endl;
        }

    }
};


std::string source = R"({marketplace = {
    cost = 100
    time = 12
    colors = {255 255 255}
    modifier = {
        province_trade_power_modifier = 0.5
    }
}
})";

int main() {
    std::ifstream t("c:\\Users\\jarvi\\Documents\\Paradox Interactive\\Europa Universalis IV\\save games\\lubeck.eu4");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string input = buffer.str();
    int index = input.find("EU4txt");
    if(index != -1){
        input.erase(0,6);
    }
    Lexer lexer('{'+input+'}');



    Parser parser(lexer);

    std::unique_ptr<Node> ast = parser.parse();
    std::cout<< "Done! " << std::endl;
    std::string json = ast->toJSON();
    std::ofstream wf("student.dat", std::ios::out);
    wf << json;
    wf.close();
    std::cout << json.length() << std::endl;

    return 0;
}