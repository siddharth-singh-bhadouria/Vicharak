#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "CodeGenerator.h"

int main()
{
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open input file.\n";
        return 1;
    }

    Lexer lexer(inputFile);

    try
    {
        Parser parser(lexer);
        ASTNode *astRoot = parser.parse();

        CodeGenerator codeGen;
        codeGen.generate(astRoot);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    inputFile.close();

    return 0;
}