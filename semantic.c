#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "symbol.h"

char* evalType(ASTNode* node) {

    switch(node->type) {

        case AST_INT_LITERAL:
            return "integer";

        case AST_REAL_LITERAL:
            return "real";

        case AST_CHAR_LITERAL:
            return "char";

        case AST_STRING_LITERAL:
            return "literal";

        case AST_BOOL_LITERAL:
            return "bool";

        case AST_IDENTIFIER: {

            char* t =
                findSymbol(node->value);

            if(!t) {
                printf("Variavel nao declarada %s\n",
                       node->value);
                exit(1);
            }

            return t;
        }

        case AST_BINARY_OP: {

            char* left =
                evalType(node->child1);

            char* right =
                evalType(node->child2);

            if(strcmp(left,right)!=0) {

                printf("Tipos incompatíveis\n");
                exit(1);
            }

            return left;
        }

        default:
            return "void";
    }
}

void semantic(ASTNode* node) {

    while(node) {

        switch(node->type) {

            case AST_VAR_DECL: {

                char* varType =
                    node->child1->value;

                insertSymbol(
                    node->value,
                    varType
                );

                char* exprType =
                    evalType(node->child2);

                if(strcmp(varType,exprType)!=0) {

                    printf(
                        "Erro semantico em %s\n",
                        node->value
                    );

                    exit(1);
                }

                break;
            }

            case AST_ASSIGN: {

                char* varType =
                    findSymbol(node->value);

                if(!varType) {

                    printf(
                       "Variavel nao declarada %s\n",
                       node->value
                    );

                    exit(1);
                }

                char* exprType =
                    evalType(node->child1);

                if(strcmp(varType,exprType)!=0) {

                    printf(
                       "Atribuicao invalida %s\n",
                       node->value
                    );

                    exit(1);
                }

                break;
            }

            default:
                break;
        }

        semantic(node->child1);
        semantic(node->child2);
        semantic(node->child3);
        semantic(node->child4);

        node = node->next;
    }
}
