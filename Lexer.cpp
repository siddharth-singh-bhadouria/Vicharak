#include "Lexer.h"
#include <cctype>
#include <cstring>

Lexer::Lexer(std::istream &input) : input(input) {}

Token Lexer::getNextToken()
{
    char c;
    while (input.get(c))
    {
        if (isspace(c))
            continue;

        if (isalpha(c))
        {
            std::string identifier(1, c);
            while (input.get(c) && (isalnum(c) || c == '_'))
            {
                identifier += c;
            }
            input.unget();
            if (identifier == "int")
                return {TOKEN_INT, identifier};
            if (identifier == "if")
                return {TOKEN_IF, identifier};
            return {TOKEN_IDENTIFIER, identifier};
        }

        if (isdigit(c))
        {
            std::string number(1, c);
            while (input.get(c) && isdigit(c))
            {
                number += c;
            }
            input.unget();
            return {TOKEN_NUMBER, number};
        }

        switch (c)
        {
        case '=':
            return {TOKEN_ASSIGN, "="};
        case '+':
            return {TOKEN_PLUS, "+"};
        case '-':
            return {TOKEN_MINUS, "-"};
        case '{':
            return {TOKEN_LBRACE, "{"};
        case '}':
            return {TOKEN_RBRACE, "}"};
        case ';':
            return {TOKEN_SEMICOLON, ";"};
        }
    }
    return {TOKEN_EOF, ""};
}