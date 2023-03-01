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

int numChars = 0;
int capacity = 256;
char* postFix;
int currentRegister = 0;
char* lhsID;
int numExpressions;

void startParser(char* fileName) {
  lookahead = 0;

  lhsID = malloc(sizeof(char*) * capacity);
  symbolTable = initSymbolTable();
  initLexer(fileName, symbolTable);

  match(lookahead);
  match(BEGIN);
  do {
    while (lookahead == INT) {
      match(INT);
      declaration();
    }
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
  int type = lookup(getIdLexeme());
  if (type == NOT_FOUND) {
    set(symbolTable, getIdLexeme(), ID);
  } else {
    // redeclaration
    error(Redeclaration, getLineNum(), getColNum());
  }
  match(ID);
}
void assignmentStmt() {
  postFix = malloc(sizeof(char) * capacity);
  numChars = 0;
  numExpressions = 0;
  currentRegister = 0;
  // registers[currentRegister] = *getIdLexeme();
  lhsID = getIdLexeme();

  match(ID);
  if (lookahead != '=') {
    // assignment stuff
    error(M_Assignment_Op, getLineNum(), getColNum());
    exit(1);
  } else {
    match(lookahead);
    numExpressions++;
    expression();
    // printf("R%d = %s\n", currentRegister++, getIdLexeme());

    // if (currentRegister >= 0)
    // printf("R%d = R%d\n", currentRegister, currentRegister);
    //   // currentRegister++;
    // }
    match(';');
  }
  printf("%s = R%d\n", lhsID, currentRegister -= numExpressions);
  if (numChars > 1)
    printf("*****[%s]*****\n", postFix);
}

void expression() {
  term();
  while (lookahead == '+' || lookahead == '-') {
    int opCode = lookahead;
    match(lookahead);
    term();
    currentRegister -= 2;
    printf("R%d = R%d %c R%d\n", currentRegister, currentRegister, opCode,
           ++currentRegister);
    // printf("%c,", opCode);
    char charOpCode = opCode + '\0';
    strncat(postFix, &charOpCode, 1);
    numChars++;
  }
}

void term() {
  factor();
  while (lookahead == '*' || lookahead == '/') {
    int opCode = lookahead;
    match(lookahead);
    factor();
    // printf("%c,", opCode);
    printf("R%d = R%d %c R%d\n", currentRegister, currentRegister, opCode,
           ++currentRegister);
    char charOpCode = opCode + '\0';
    strncat(postFix, &charOpCode, 1);
    numChars++;
  }
}

void factor() {
  if (lookahead == ID) {
    printf("R%d = %s\n", currentRegister++, getIdLexeme());
    // printf("%s", getIdLexeme());    //prints the lexeme for postfix
    strcat(postFix, getIdLexeme());
    numChars++;
    match(ID);
    // currentRegister--;
  } else if (lookahead == NUM) {
    printf("R%d = %s\n", currentRegister++, getNumLexeme());
    strcat(postFix, getNumLexeme());
    numChars++;
    // printf("%s", getNumLexeme());
    match(NUM);
  } else if (lookahead == '(') {
    match('(');
    numExpressions++;
    expression();
    currentRegister--;
    numExpressions--;
    // printf("R%d = %s\n", currentRegister++, getIdLexeme());
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