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
  symbolTable = initSymbolTable();
  initLexer(fileName, symbolTable);

  match(lookahead);
  match(BEGIN);
  do {
    while (lookahead == INT) {
      printf("lookahead before declaration  = %d\n", lookahead);
      match(INT);
      declaration();
    }
    printf("calling assignment statement. lookahead = %d\n", lookahead);
    assignmentStmt();
  } while (lookahead == ID);
  match(END);
  end(0);
}

void declaration() {
  while (lookahead != ';' && lookahead != INT) {
    getIdDeclaration();
    while (lookahead == ',') {
      match(',');
      getIdDeclaration();
    }
    match(';');
    if (lookahead != INT) {
      break;
    }
  }
}

void getIdDeclaration() {
  // printf("got into get id declaration\n");
  int type = lookup(getIdLexeme());
  if (type == NOT_FOUND) {
    // printf("id = %s\n", getIdLexeme());
    set(symbolTable, getIdLexeme(), ID);
  } else {
    // printf("error\n");
    // redeclaration
    error(Redeclaration, getLineNum(), getColNum());
  }
  // printf("matching ID for id: %s\n", getIdLexeme());
  match(ID);
}
void assignmentStmt() {
  printf("lookahead = %d, %s\n", lookahead, getIdLexeme());

  match(ID);
  if (lookahead != '=') {
    // assignment stuff
    error(M_Assignment_Op, getLineNum(), getColNum());
    exit(1);
  } else {
    match(lookahead);
    printf("lookahead = %d, %s\n", lookahead, getIdLexeme());
    expression();
    match(';');
  }
}

void expression() {
  term();
  while (lookahead == '+' || lookahead == '-') {
    printf("[*****%d, %c*****]\n", lookahead, lookahead);
    if (lookahead == '+') {
      printf("[*****%d, %c*****]\n", lookahead, lookahead);

      match(lookahead);
      term();
      // printf("[*****%c, %c, %c*****]\n", );
    }
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
  printf("Error:");
  if (error == M_End) {
    printf("Syntax error on line %d, col %d. All programs must end with "
           "'end.'\n",
           line, col);
  } else if (error == M_ClosingParen) {
    printf("Missing closing parenthesis on line %d, col %d.\n", line, col);
  } else if (error == M_Begin) {
    printf("Syntax error on line %d, col %d. All programs must begin with "
           "'begin'\n",
           line, col);
  } else if (error == M_Semicolon) {
    printf("Syntax error on line %d, col %d. Every assignment statement must "
           "end with a semicolon -> ';'",
           line, col);
  } else if (error == General_Syntax_Error) {
    printf("Syntax error on line %d, col %d.\n", line, col);
  } else if (error == M_Assignment_Op) {
    printf("Expected an '=' on line %d, col %d\nFailure!\n", line, col);
  } else if (error == Redeclaration) {
    printf("Cannot define id: %s on line %d col %d because it has already been "
           "defined elsewhere (redefinition error)\n",
           getIdLexeme(), line, col);
  }
  exit(1);
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