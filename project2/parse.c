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
FILE* logs;
char* logFile = "./logs.txt";

void startParser(char* fileName) {
  lookahead = 0;
  logs = fopen(logFile, "w");
  fclose(logs);
  logs = fopen(logFile, "a");
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
  // logs = fopen(logFile, "a");
  postFix = malloc(sizeof(char) * capacity);
  numChars = 0;
  numExpressions = 0;
  currentRegister = 0;
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
    match(';');
  }
  char string[256];
  memset(string, '\0', 256);
  sprintf(string, "%s = R%d\n", lhsID, currentRegister -= numExpressions);
  // char string[256];
  fputs(string, logs);
  // fclose(logs);
  if (numChars > 1) {

    char string[256];
    memset(string, '\0', 256);
    sprintf(string, "*****[%s]*****\n", postFix);
    fputs(string, logs);
    // fclose(logs);
  }
}

void expression() {
  term();
  while (lookahead == '+' || lookahead == '-') {
    int opCode = lookahead;
    match(lookahead);
    term();
    char string[256];
    memset(string, '\0', 256);
    sprintf(string, "R%d = R%d %c R%d\n", currentRegister - 2,
            currentRegister - 2, opCode, currentRegister - 1);
    fputs(string, logs);

    --currentRegister;

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

    char string[256];
    memset(string, '\0', 256);
    sprintf(string, "R%d = R%d %c R%d\n", currentRegister - 2,
            currentRegister - 2, opCode, currentRegister - 1);
    fputs(string, logs);
    --currentRegister;

    char charOpCode = opCode + '\0';
    strncat(postFix, &charOpCode, 1);
    numChars++;
  }
}

void factor() {
  if (lookahead == ID) {
    if (lookup(getIdLexeme()) == NOT_FOUND) {
      printf("error, cannot assign to an undeclared id\n");
      end(1);
    }
    char string[256];
    memset(string, '\0', 256);
    sprintf(string, "R%d = %s\n", currentRegister++, getIdLexeme());
    fputs(string, logs);

    strcat(postFix, getIdLexeme());
    numChars++;
    match(ID);
  } else if (lookahead == NUM) {
    // printf("R%d = %d\n", currentRegister++, atoi(getNumLexeme()));

    char string[256];
    memset(string, '\0', 256);
    sprintf(string, "R%d = %d\n", currentRegister++, atoi(getNumLexeme()));
    fputs(string, logs);
    sprintf(postFix, "%s%d\0", postFix, atoi(getNumLexeme()));
    numChars++;
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
  fclose(logs);
  logs = fopen(logFile, "rb");
  char ch;

  do {
    ch = fgetc(logs);
    if (ch == EOF)
      break;

    if (ch != '\n' && (ch < 32 || ch > 122)) {
      continue;
    }

    printf("%c", ch);
  } while (!feof(logs));
  fclose(logs);
  // readLogs();
  // printf("a\n");
  dumpType(symbolTable, ID);
  destroy(symbolTable);
  exit(EXIT_SUCCESS);
}