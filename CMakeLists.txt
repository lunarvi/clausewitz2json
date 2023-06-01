cmake_minimum_required(VERSION 3.25)
project(parser2)

set(CMAKE_CXX_STANDARD 17)

add_executable(parser2 main.cpp TokenType.h Node.h Lexer.h Token.h Lexer.cpp Token.cpp TokenType.cpp Node.cpp)
