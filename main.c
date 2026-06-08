#include <stdio.h>

#include "ast.h"

// Léxica
void initLexer(const char *filename);
void closeLexer();

// Sintática
ASTNode* parseProgram();

// Semântica
void semantic(ASTNode* node);

int main() {

    printf("Iniciando compilacao...\n");

    initLexer("codigo.star");

    ASTNode* root = parseProgram();

    printf("Analise sintatica concluida com sucesso!\n");

    semantic(root);

    printf("Analise semantica concluida com sucesso!\n");

    closeLexer();

    printf("Compilacao finalizada sem erros.\n");

    return 0;
}
