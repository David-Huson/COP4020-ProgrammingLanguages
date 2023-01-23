/**
 * @file parse.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "parse.h"
#include "baseTypes.h"
#include "lexer.h"

void startParser(char* fileName) {
  lookahead = 0;
  initLexer(fileName);
  match(lookahead);
  match(lookup(BEGIN));
  assignmentStmt();
}

void assignmentStmt() {
  match(getType(ID));
  if (lookahead != '=') {
    printf("error on line: %d in assignStmt()\n", getLineNum());
  } else {
    match(lookahead);
    expression();
    match(';');
  }
}

void expression() {
  term();
  while (lookahead == '+' || lookahead == '-') {
    printf("found an expression\n");
    match(lookahead);
    term();
  }
}

void term() {
  factor();
  while (lookahead == '*' || lookahead == '/') {
    printf("found a term\n");
    match(lookahead);
    factor();
  }
}

void factor() {
  if (lookahead == getType(ID)) {
    printf("found an ID\n");
    match(getType(ID));
  } else if (lookahead == getType(NUM)) {
    printf("found a NUM\n");
    match(getType(NUM));
  } else if (lookahead == '(') {
    printf("open paren\n");
    match('(');
    expression();
    printf("closed paren\n");
    match(')');
  } else {
    printf("syntax error in factor() at line: %d\n", getLineNum());
  }
}

void match(int type) {
  // printf("lookahead = %d, match type = %d\n", lookahead, type);
  if (lookahead == type) {
    // printf("matching %d\n", type);
    lookahead = lexan();
    // printf("lookahead now = %d\n", lookahead);
  } else
    printf("Syntax error in match() at line: %d\n", getLineNum());
}

void end() {
  // while (1) {
  //   Entity* e = get(symbolTable, lookup(ID));
  //   if (e == NULL)
  //     break;

  //   printf("Identifier: %s\n", e->value);
  // }
  dump(symbolTable);
  destroy(symbolTable);
}