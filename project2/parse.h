#ifndef PARSE_H_
#define PARSE_H_

#include <stdio.h>

typedef enum {
  M_Semicolon,
  M_ClosingParen,
  M_Begin,
  M_End,
  M_Assignment_Op,
  General_Syntax_Error,
} ErrorTypes;
int lookahead;

void startParser(char* fileName);
void declaration();
void assignmentStmt();
void expression();
void term();
void factor();
void match(int type);
void end();
void error(ErrorTypes error, int line, int col);
#endif