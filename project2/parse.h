#ifndef PARSE_H_
#define PARSE_H_

#include "symbolTable.h"
#include <stdio.h>

typedef enum {
  M_Semicolon,
  M_ClosingParen,
  M_Begin,
  M_End,
  M_Assignment_Op,
  Redeclaration,
  General_Syntax_Error,
} ErrorTypes;
int lookahead;
HashTable* symbolTable;

void startParser(char* fileName);
void declaration();
void assignmentStmt();
void expression();
void term();
void factor();
void match(int type);
void end();
void error(ErrorTypes error, int line, int col);
void getIdDeclaration();
void readlogs();
void write(char* string);
void readLogs();
#endif