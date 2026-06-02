#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <string.h>

typedef enum {

    AST_PROGRAM,

    AST_VAR_DECL,
    AST_ASSIGN,

    AST_IF,
    AST_FOR,
    AST_BLOCK,

    AST_BINARY_OP,

    AST_IDENTIFIER,

    AST_INT_LITERAL,
    AST_REAL_LITERAL,
    AST_CHAR_LITERAL,
    AST_STRING_LITERAL,
    AST_BOOL_LITERAL

} ASTNodeType;

typedef struct ASTNode {

    ASTNodeType type;

    char value[256];

    struct ASTNode* child1;
    struct ASTNode* child2;
    struct ASTNode* child3;
    struct ASTNode* child4;

    struct ASTNode* next;

} ASTNode;

static ASTNode* createNode(ASTNodeType type, const char* value) {

    ASTNode* node = malloc(sizeof(ASTNode));

    node->type = type;

    if(value)
        strcpy(node->value, value);
    else
        node->value[0] = '\0';

    node->child1 = NULL;
    node->child2 = NULL;
    node->child3 = NULL;
    node->child4 = NULL;
    node->next = NULL;

    return node;
}

#endif
