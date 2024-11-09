#include "Parser.h"
#include <stdexcept>

Parser::Parser(Lexer &lexer) : lexer(lexer), currentToken(lexer.getNextToken()) {}

void Parser::eat(TokenType type)
{
    if (currentToken.type == type)
    {
        currentToken = lexer.getNextToken();
    }
    else
    {
        throw std::runtime_error("Unexpected token");
    }
}

ASTNode *Parser::parse()
{
    return program();
}

ASTNode *Parser::program()
{
    std::vector<ASTNode *> statements;

    while (currentToken.type != TOKEN_EOF)
    {
        statements.push_back(statement());
    }

    // For simplicity, we won't create a full program node.
    return statements.empty() ? nullptr : statements[0];
}

ASTNode *Parser::statement()
{
    if (currentToken.type == TOKEN_INT)
    {
        eat(TOKEN_INT);
        VarDeclNode *varDecl = new VarDeclNode();
        varDecl->name = currentToken.text;
        eat(TOKEN_IDENTIFIER);
        eat(TOKEN_SEMICOLON);
        return varDecl;
    }
    else if (currentToken.type == TOKEN_IDENTIFIER)
    {
        AssignNode *assign = new AssignNode();
        assign->varName = currentToken.text;
        eat(TOKEN_IDENTIFIER);
        eat(TOKEN_ASSIGN);
        assign->expr = expression();
        eat(TOKEN_SEMICOLON);
        return assign;
    }
    else if (currentToken.type == TOKEN_IF)
    {
        eat(TOKEN_IF);
        eat(TOKEN_LBRACE); // Assuming condition is just an identifier for simplicity
        IfNode *ifStmt = new IfNode();
        ifStmt->condition = expression(); // Placeholder for condition
        eat(TOKEN_RBRACE);
        ifStmt->thenBranch = statement(); // Assuming single statement for simplicity
        return ifStmt;
    }

    throw std::runtime_error("Invalid statement");
}

ASTNode *Parser::expression()
{
    // Simplified expression handling for numbers and variables.
    if (currentToken.type == TOKEN_NUMBER)
    {
        NumberNode *number = new NumberNode();
        number->value = std::stoi(currentToken.text);
        eat(TOKEN_NUMBER);
        return number;
    }
    else if (currentToken.type == TOKEN_IDENTIFIER)
    {
        VarDeclNode *var = new VarDeclNode();
        var->name = currentToken.text;
        eat(TOKEN_IDENTIFIER);
        return var; // Return variable reference
    }

    throw std::runtime_error("Invalid expression");
}