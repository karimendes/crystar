#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "ast.h"

extern Token getNextToken();

Token currentToken;

void advance() {
    currentToken = getNextToken();
}

void syntaxError(const char* msg) {

    printf("\nERRO SINTATICO\n");
    printf("%s\n", msg);
    printf("Token encontrado: %s\n", currentToken.lexeme);

    exit(1);
}

void eat(TokenType expected) {

    if(currentToken.type == expected)
        advance();
    else
        syntaxError("token inesperado");
}

int isType(TokenType t) {

    return t == TOK_INTEGER ||
           t == TOK_REAL ||
           t == TOK_CHAR ||
           t == TOK_LITERAL ||
           t == TOK_BOOL;
}

ASTNode* parseExpression();

ASTNode* parseFactor() {

    ASTNode* node;

    switch(currentToken.type) {

        case TOK_ID:

            node = createNode(
                AST_IDENTIFIER,
                currentToken.lexeme
            );

            eat(TOK_ID);

            return node;

        case TOK_INT_LITERAL:

            node = createNode(
                AST_INT_LITERAL,
                currentToken.lexeme
            );

            eat(TOK_INT_LITERAL);

            return node;

        case TOK_REAL_LITERAL:

            node = createNode(
                AST_REAL_LITERAL,
                currentToken.lexeme
            );

            eat(TOK_REAL_LITERAL);

            return node;

        case TOK_CHAR_LITERAL:

            node = createNode(
                AST_CHAR_LITERAL,
                currentToken.lexeme
            );

            eat(TOK_CHAR_LITERAL);

            return node;

        case TOK_STRING_LITERAL:

            node = createNode(
                AST_STRING_LITERAL,
                currentToken.lexeme
            );

            eat(TOK_STRING_LITERAL);

            return node;

        case TOK_TRUE:
        case TOK_FALSE:

            node = createNode(
                AST_BOOL_LITERAL,
                currentToken.lexeme
            );

            advance();

            return node;

        case TOK_LEFT_PAREN:

            eat(TOK_LEFT_PAREN);

            node = parseExpression();

            eat(TOK_RIGHT_PAREN);

            return node;

        default:
            syntaxError("fator invalido");
    }

    return NULL;
}

ASTNode* parseTerm() {

    ASTNode* left = parseFactor();

    while(currentToken.type == TOK_MULT ||
          currentToken.type == TOK_DIV) {

        char op[10];
        strcpy(op, currentToken.lexeme);

        advance();

        ASTNode* right = parseFactor();

        ASTNode* node =
            createNode(AST_BINARY_OP, op);

        node->child1 = left;
        node->child2 = right;

        left = node;
    }

    return left;
}

ASTNode* parseArithmetic() {

    ASTNode* left = parseTerm();

    while(currentToken.type == TOK_PLUS ||
          currentToken.type == TOK_MINUS) {

        char op[10];
        strcpy(op, currentToken.lexeme);

        advance();

        ASTNode* right = parseTerm();

        ASTNode* node =
            createNode(AST_BINARY_OP, op);

        node->child1 = left;
        node->child2 = right;

        left = node;
    }

    return left;
}

ASTNode* parseExpression() {

    ASTNode* left = parseArithmetic();

    if(currentToken.type == TOK_GT ||
       currentToken.type == TOK_GTE ||
       currentToken.type == TOK_LT ||
       currentToken.type == TOK_LTE ||
       currentToken.type == TOK_EQ ||
       currentToken.type == TOK_NE) {

        char op[10];
        strcpy(op, currentToken.lexeme);

        advance();

        ASTNode* right = parseArithmetic();

        ASTNode* node =
            createNode(AST_BINARY_OP, op);

        node->child1 = left;
        node->child2 = right;

        return node;
    }

    return left;
}

ASTNode* parseVarDecl() {

    char type[50];
    strcpy(type, currentToken.lexeme);

    advance();

    char id[100];
    strcpy(id, currentToken.lexeme);

    eat(TOK_ID);

    eat(TOK_ASSIGN);

    ASTNode* expr = parseExpression();

    eat(TOK_SEMICOLON);

    ASTNode* node =
        createNode(AST_VAR_DECL, id);

    node->child1 =
        createNode(AST_IDENTIFIER, type);

    node->child2 = expr;

    return node;
}

ASTNode* parseAssignmentNoSemi() {

    char id[100];
    strcpy(id, currentToken.lexeme);

    eat(TOK_ID);

    eat(TOK_ASSIGN);

    ASTNode* expr = parseExpression();

    ASTNode* node =
        createNode(AST_ASSIGN, id);

    node->child1 = expr;

    return node;
}

ASTNode* parseAssignment() {

    ASTNode* node =
        parseAssignmentNoSemi();

    eat(TOK_SEMICOLON);

    return node;
}

ASTNode* parseCommand();

ASTNode* parseBlock() {

    eat(TOK_LEFT_BRACE);

    ASTNode* block =
        createNode(AST_BLOCK, "");

    ASTNode* last = NULL;

    while(currentToken.type != TOK_RIGHT_BRACE) {

        ASTNode* cmd =
            parseCommand();

        if(last == NULL)
            block->child1 = cmd;
        else
            last->next = cmd;

        last = cmd;
    }

    eat(TOK_RIGHT_BRACE);

    return block;
}

ASTNode* parseIf() {

    eat(TOK_IF);

    eat(TOK_LEFT_PAREN);

    ASTNode* cond =
        parseExpression();

    eat(TOK_RIGHT_PAREN);

    ASTNode* thenBlock =
        parseBlock();

    ASTNode* elseBlock = NULL;

    if(currentToken.type == TOK_ELSE) {

        eat(TOK_ELSE);

        elseBlock = parseBlock();
    }

    ASTNode* node =
        createNode(AST_IF, "if");

    node->child1 = cond;
    node->child2 = thenBlock;
    node->child3 = elseBlock;

    return node;
}

ASTNode* parseFor() {

    eat(TOK_FOR);

    eat(TOK_LEFT_PAREN);

    ASTNode* init =
        parseAssignmentNoSemi();

    eat(TOK_SEMICOLON);

    ASTNode* cond =
        parseExpression();

    eat(TOK_SEMICOLON);

    ASTNode* inc =
        parseAssignmentNoSemi();

    eat(TOK_RIGHT_PAREN);

    ASTNode* body =
        parseBlock();

    ASTNode* node =
        createNode(AST_FOR, "for");

    node->child1 = init;
    node->child2 = cond;
    node->child3 = inc;
    node->child4 = body;

    return node;
}

ASTNode* parseCommand() {

    if(currentToken.type == TOK_IF)
        return parseIf();

    if(currentToken.type == TOK_FOR)
        return parseFor();

    if(currentToken.type == TOK_LEFT_BRACE)
        return parseBlock();

    if(currentToken.type == TOK_ID)
        return parseAssignment();

    syntaxError("comando invalido");

    return NULL;
}

ASTNode* parseProgram() {

    advance();

    ASTNode* root =
        createNode(AST_PROGRAM, "program");

    ASTNode* last = NULL;

    while(currentToken.type != TOK_EOF) {

        ASTNode* node;

        if(isType(currentToken.type))
            node = parseVarDecl();
        else
            node = parseCommand();

        if(last == NULL)
            root->child1 = node;
        else
            last->next = node;

        last = node;
    }

    return root;
}
