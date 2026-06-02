#ifndef SYMBOL_H
#define SYMBOL_H

#define MAX_SYMBOLS 1000

typedef struct {

    char name[100];
    char type[50];

} Symbol;

extern Symbol table[MAX_SYMBOLS];
extern int symbolCount;

void insertSymbol(char* name,char* type);
char* findSymbol(char* name);

#endif
