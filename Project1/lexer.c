/**
 * @file lexer.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "lexer.h"
#include "symbolTable.h"

void initLexer(char* fileName) {
  lineNumber = 0;
  symbolTable = initSymbolTable();
  dump(symbolTable);
  file = fopen(fileName, "r");
}

int lexan() {
  char ch = fgetc(file);

  do {
    if (ch == ' ' || ch == '\t') {
      // printf("whitespace\n");
      ch = fgetc(file);
      // printf("Next char: %c\n", ch);
    } else if (ch == '\n') {
      // printf("newline\n");
      lineNumber++;
      ch = fgetc(file);
    } else if (ch == '~') {
      // printf("comment\n");
      while (strcmp(&ch, "\n") != 0) {
        ch = fgetc(file);
      }
    } else if (isdigit(ch)) {
      // printf("number\n");
      int numChars = 0;
      char* numLexan = malloc(sizeof(char*));
      while (isdigit(ch)) {
        numLexan = realloc(numLexan, ++numChars * sizeof(char));
        strncat(numLexan, &ch, numChars + 1);
        ch = fgetc(file);
      }
      return lookup(NUM);

    } else if (isalpha(ch)) {
      // printf("ident\n");
      // // printf("entered id loop\n");
      int numChars = 0;
      int capacity = 256;
      char* idLexan = malloc(sizeof(char) * capacity);
      while (isalpha(ch) && ch != '\n') {

        if (numChars == capacity - 1) {
          idLexan = realloc(idLexan, sizeof(char) * capacity);
        }

        idLexan[numChars++] = ch;
        ch = fgetc(file);
      }
      // // printf("ID = %s\n", idLexan);
      char temp = ch;
      ch = ungetc(ch, file);
      int type = lookup(idLexan);
      // printf("type = %d\n", type);
      if (type == lookup(NOT_FOUND)) {
        type = lookup(ID);
        set(symbolTable, idLexan, type);
        // printf("type = %d\n", type);
        return lookup(ID);
      }
      return type;

    } else if (ch == EOF) {
      return lookup(DONE);
    } else {
      return ch;
    }
  } while (!feof(file));
  return lookup(NOT_FOUND);
}

int getType(char* key) { return lookup(key); }

int getLineNum() { return lineNumber; }