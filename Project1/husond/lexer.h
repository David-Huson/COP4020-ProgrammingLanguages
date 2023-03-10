/******************************************************************************
        Project 1
        @name David Huson
        @file lexer.h

        @brief this file contains the funciton definitions and boilerplate for a
                                        lexical analiyzer.
******************************************************************************/
#ifndef LEXAN_H
#define LEXAN_H

#include "baseTypes.h"
#include "symbolTable.h"
#include <ctype.h>

/**
 * @brief analyze the input and determine then return the token type; If the
 * token does not exist in the symbol table, add it.
 *
 * @return int tokenType
 */

int numLexan;
char idLexan;
static FILE* file;
HashTable* symbolTable;

void initLexer(char* fileName);
int lexan();
int getType(char* key);
int getLineNum();
int getColNum();

#endif