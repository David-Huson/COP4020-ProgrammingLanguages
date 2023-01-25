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
  match(BEGIN);
  assignmentStmt();
}

void assignmentStmt() {
  match(ID);
  if (lookahead != '=') {
    if (lookahead == DONE) {
      end();
    } else {
      printf("error on line: %d in assignStmt()\n", getLineNum());
      end();
    }
  } else {
    match(lookahead);
    expression();
    match(';');
  }
}

void expression() {
  term();
  while (lookahead == '+' || lookahead == '-') {
    // printf("found an expression\n");
    match(lookahead);
    term();
  }
}

void term() {
  factor();
  while (lookahead == '*' || lookahead == '/') {
    // printf("found a term\n");
    match(lookahead);
    factor();
  }
}

void factor() {
  if (lookahead == ID) {
    match(ID);
  } else if (lookahead == NUM) {
    match(NUM);
  } else if (lookahead == '(') {
    match('(');
    expression();
    match(')');
  } else {
    printf("syntax error in factor() at line: %d\n", getLineNum());
    end();
  }
}

void match(int type) {
  // printf("lookahead = %d, match type = %d\n", lookahead, type);
  if (lookahead == type) {
    // printf("matching %d\n", type);
    lookahead = lexan();
    // printf("lookahead now = %d\n", lookahead);
  } else if (lookahead == DONE) {
    end();
  }
}

void end() {

  // dump(symbolTable);
  dumpType(symbolTable, ID);
  destroy(symbolTable);
  exit(EXIT_FAILURE);
}