#include "CodeGenerator.h"
#include <iostream>

void CodeGenerator::generate(ASTNode *node)
{
    if (!node)
        return;

    if (auto varDecl = dynamic_cast<VarDeclNode *>(node))
    {
        generateVarDecl(varDecl);
    }
    else if (auto assign = dynamic_cast<AssignNode *>(node))
    {
        generateAssign(assign);
    }
    else if (auto number = dynamic_cast<NumberNode *>(node))
    {
        generateNumber(number);
    }
    else if (auto binaryOp = dynamic_cast<BinaryOpNode *>(node))
    {
        generateBinaryOp(binaryOp);
    }
    else if (auto ifStmt = dynamic_cast<IfNode *>(node))
    {
        generateIf(ifStmt);
    }

    delete node; // Clean up node after processing
}

void CodeGenerator::generateVarDecl(VarDeclNode *node)
{
    std::cout << "DECLARE " << node->name << "\n";
}

void CodeGenerator::generateAssign(AssignNode *node)
{
    std::cout << "LOAD " << node->expr << "\n"; // Placeholder for loading expression
    std::cout << "STORE " << node->varName << "\n";
}

void CodeGenerator::generateNumber(NumberNode *node)
{
    std::cout << "PUSH " << node->value << "\n";
}

void CodeGenerator::generateBinaryOp(BinaryOpNode *node)
{
    generate(node->left);
    generate(node->right);

    if (node->op == '+')
        std::cout << "ADD\n";
    else
        std::cout << "SUB\n";
}

void CodeGenerator::generateIf(IfNode *node)
{
    generate(node->condition);
    std::cout << "JUMP_IF_FALSE END_IF\n";
    generate(node->thenBranch);
    std::cout << "LABEL END_IF\n";
}