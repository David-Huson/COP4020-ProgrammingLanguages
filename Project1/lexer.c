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
      return NUM;

    } else if (isalpha(ch)) {
      // printf("ident\n");
      // printf("entered id loop\n");

      int numChars = 0;
      int capacity = 256;
      char* idLexan = malloc(sizeof(char) * capacity);
      while ((isalnum(ch) || ch == '_') && ch != '\n') {
        if (numChars == capacity - 1) {
          idLexan = realloc(idLexan, sizeof(char) * capacity);
        }

        if (ch == '_') {
          char nextChar = fgetc(file);
          if (nextChar == '_') {
            printf("Syntax error on line: %d, Identifiers cannot contain "
                   "consecutive underscores ('_').\n",
                   lineNumber);
            free(idLexan);
            return DONE;
          }
          nextChar = ungetc(nextChar, file);
        }

        idLexan[numChars++] = ch;
        ch = fgetc(file);
      }

      if (idLexan[strlen(idLexan) - 1] == '_') {
        printf("Syntax error on line: %d, Identifiers cannot "
               "end with underscores ('_').\n",
               lineNumber);
        free(idLexan);
        return DONE;
      }
      // printf("idLexan = %s\n", idLexan);
      ch = ungetc(ch, file);
      int type = lookup(idLexan);
      // printf("type = %d\n", type);
      if (type == NOT_FOUND) {
        if (strcmp(idLexan, "begin") == 0) {
          type = BEGIN;
        } else if (strcmp(idLexan, "end") == 0) {
          type = END;
        } else {
          type = ID;
        }

        set(symbolTable, idLexan, type);
        free(idLexan);
        // printf("type = %d\n", type);
        return type;
      }
      return type;

    } else if (ch == EOF) {
      return DONE;
    } else {
      return ch;
    }
  } while (!feof(file));
  return NOT_FOUND;
}

int getLineNum() { return lineNumber; }