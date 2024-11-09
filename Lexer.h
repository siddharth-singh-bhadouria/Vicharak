#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>

enum TokenType
{
    TOKEN_INT,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_ASSIGN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_IF,
    TOKEN_EQUAL,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOLON,
    TOKEN_EOF
};

struct Token
{
    TokenType type;
    std::string text;
};

class Lexer
{
public:
    Lexer(std::istream &input);
    Token getNextToken();

private:
    std::istream &input;
};

#endif // LEXER_H