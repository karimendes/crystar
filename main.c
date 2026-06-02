#include <stdio.h>

#include "token.h"
#include "ast.h"

void initLexer(const char *filename);
void closeLexer();

ASTNode* parseProgram();

void printAST(ASTNode* node, int level);

int main() {

    initLexer("codigo.star");

    ASTNode* ast = parseProgram();

    printf("\n===== AST =====\n\n");

    printAST(ast, 0);

    closeLexer();

    return 0;
}
