#ifndef TOKEN_H
#define TOKEN_H

#define MAX_LEXEMA 256

typedef enum {
    TOK_ID,

    TOK_INTEGER,
    TOK_REAL,
    TOK_CHAR,
    TOK_LITERAL,
    TOK_BOOL,

    TOK_IF,
    TOK_ELSE,
    TOK_FOR,

    TOK_TRUE,
    TOK_FALSE,

    TOK_VOID,
    TOK_NULL,

    TOK_INT_LITERAL,
    TOK_REAL_LITERAL,
    TOK_CHAR_LITERAL,
    TOK_STRING_LITERAL,

    TOK_PLUS,
    TOK_MINUS,
    TOK_MULT,
    TOK_DIV,
    TOK_POW,

    TOK_GT,
    TOK_GTE,
    TOK_LT,
    TOK_LTE,
    TOK_EQ,
    TOK_NE,

    TOK_ASSIGN,

    TOK_SEMICOLON,
    TOK_LEFT_BRACE,
    TOK_RIGHT_BRACE,
    TOK_LEFT_PAREN,
    TOK_RIGHT_PAREN,

    TOK_EOF,
    TOK_ERROR

} TokenType;

typedef struct {
    TokenType type;
    char lexeme[MAX_LEXEMA];
} Token;

#endif 