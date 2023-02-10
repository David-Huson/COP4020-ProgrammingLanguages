#ifndef PARSE_H_
#define PARSE_H_

#include <stdio.h>

int lookahead;
int lineNum;

void startParser(char* fileName);
void assignmentStmt();
void expression();
void term();
void factor();
void match(int type);
void end();
#endif