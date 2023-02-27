/******************************************************************************
 * @file parse.c
 * @author David Huson
 * @brief Determines if the token types are in the proper order and places.
 * @date 2023-01-22
 *
 ******************************************************************************/

#include "parse.h"
#include "baseTypes.h"
#include "lexer.h"

void startParser(char* fileName) {
  lookahead = 0;
  initLexer(fileName);
  match(lookahead);
  match(BEGIN);
  do {
    assignmentStmt();
  } while (lookahead == ID);
  match(END);
  end(0);
}

void assignmentStmt() {
  match(ID);
  if (lookahead != '=') {
    error(M_Assignment_Op, getLineNum(), getColNum());
    exit(1);
  } else {
    match(lookahead);
    expression();
    match(';');
  }
}

void expression() {
  term();
  while (lookahead == '+' || lookahead == '-') {
    match(lookahead);
    term();
  }
}

void term() {
  factor();
  while (lookahead == '*' || lookahead == '/') {
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
  }
}

void match(int type) {
  if (lookahead == type) {
    lookahead = lexan();
  } else if (type == ')') {
    error(M_ClosingParen, getLineNum(), getColNum());
    end(1);
  } else if (type == ID) {
    exit(1);
  } else if (type == BEGIN) {
    error(M_Begin, getLineNum(), getColNum());
    end(1);
  } else if (type == END) {
    error(M_End, getLineNum(), getColNum());
    end(1);
  } else if (type == ';') {
    error(M_Semicolon, getLineNum(), getColNum());
    end(1);
  } else {
    error(General_Syntax_Error, getLineNum(), getColNum());
    end(1);
  }
}

void error(ErrorTypes error, int line, int col) {
  if (error == M_End) {
    printf("Syntax error on line %d, col %d. All programs must start with "
           "'end.'\n",
           line, col);
  } else if (error == M_ClosingParen) {
    printf("Missing closing parenthesis on line %d, col %d.\n", line, col);
  } else if (error == M_Begin) {
    printf("Syntax error on line %d, col %d. All programs must start with "
           "'begin'\n",
           line, col);
  } else if (error == M_Begin) {
    printf("Syntax error on line %d, col %d. All programs must start with "
           "'begin'\n",
           line, col);
  } else if (error == M_Semicolon) {
    printf("Syntax error on line %d, col %d. Every assignment statement must "
           "end with a semicolon -> ';'"
           "'end'\n",
           line, col);
  } else if (error == General_Syntax_Error) {
    printf("Syntax error on line %d, col %d.\n", line, col);
  } else if (error == M_Assignment_Op) {
    printf("Expected an '=' on line %d, col %d\nFailure!\n", line, col);
  }
}

void end(int status) {

  if (status != 0) {
    printf("Failure!\n");
    destroy(symbolTable);
    exit(EXIT_FAILURE);
  }

  printf("Success!\n");
  dumpType(symbolTable, ID);
  destroy(symbolTable);
  exit(EXIT_SUCCESS);
}