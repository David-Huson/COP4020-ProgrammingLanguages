/******************************************************************************
        Project 1
        @name David Huson
        @file lexer.h

        @brief this file contains the funciton definitions and boilerplate for a
                                        lexical analiyzer.
******************************************************************************/
#ifndef LEXAN_H
#define LEXAN_H

#include "symbolTable.h"
#include <ctype.h>

/**
 * @brief analyze the input and determine then return the token type; If the
 * token does not exist in the symbol table, add it.
 *
 * @return int tokenType
 */
int lexan(FILE* filename, HashTable* symbolTable, int* lineNum);

#endif