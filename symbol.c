#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "symbol.h"

Symbol table[MAX_SYMBOLS];
int symbolCount = 0;

void insertSymbol(char* name,char* type) {

    for(int i=0;i<symbolCount;i++) {

        if(strcmp(table[i].name,name)==0) {

            printf("Erro semantico: variavel ja declarada %s\n",name);
            exit(1);
        }
    }

    strcpy(table[symbolCount].name,name);
    strcpy(table[symbolCount].type,type);

    symbolCount++;
}

char* findSymbol(char* name) {

    for(int i=0;i<symbolCount;i++) {

        if(strcmp(table[i].name,name)==0)
            return table[i].type;
    }

    return NULL;
}
