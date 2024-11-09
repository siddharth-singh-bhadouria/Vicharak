#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include <vector>

struct ASTNode
{
    virtual ~ASTNode() {}
};

struct VarDeclNode : ASTNode
{
    std::string name;
};

struct AssignNode : ASTNode
{
    std::string varName;
    ASTNode *expr;
};

struct NumberNode : ASTNode
{
    int value;
};

struct BinaryOpNode : ASTNode
{
    ASTNode *left;
    char op; // '+' or '-'
    ASTNode *right;
};

struct IfNode : ASTNode
{
    ASTNode *condition;
    ASTNode *thenBranch;
};

class Parser
{
public:
    Parser(Lexer &lexer);
    ASTNode *parse();

private:
    Lexer &lexer;
    Token currentToken;

    void eat(TokenType type);
    ASTNode *program();
    ASTNode *statement();
    ASTNode *expression();
};

#endif // PARSER_H