#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Parser.h"

class CodeGenerator
{
public:
    void generate(ASTNode *node);

private:
    void generateVarDecl(VarDeclNode *node);
    void generateAssign(AssignNode *node);
    void generateNumber(NumberNode *node);
    void generateBinaryOp(BinaryOpNode *node);
    void generateIf(IfNode *node);
};

#endif // CODEGENERATOR_H