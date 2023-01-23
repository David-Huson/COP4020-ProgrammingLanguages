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

int numLexan;
char idLexan;

int lexan(FILE* file, HashTable* symbolTable, int* lineNum) {
  char ch = fgetc(file);
  do {
    if (ch == ' ' || ch == '\t') {
      printf("whitespace\n");
      continue;
    } else if (ch == '\n') {
      printf("newline\n");
      *lineNum++;
      ch = fgetc(file);
    } else if (ch == '~') {
      printf("found a comment\n");
      while (strcmp(&ch, "\n") != 0) {
        ch = fgetc(file);
      }
    } else if (isdigit(ch)) {
      int numChars = 0;
      char* numLexan = malloc(sizeof(char*));
      while (isdigit(ch)) {
        numLexan = realloc(numLexan, ++numChars * sizeof(char));
        strncat(numLexan, &ch, numChars + 1);
        ch = fgetc(file);
      }

      printf("%s\n", numLexan);
      return lookup(NUM);

    } else if (isalpha(ch)) {
      int numChars = 0;
      char* idLexan = malloc(sizeof(char*));
      while (isalpha(ch)) {
        idLexan = realloc(idLexan, ++numChars * sizeof(char));
        strncat(idLexan, &ch, numChars + 1);
        ch = fgetc(file);
      }

      ch = ungetc(1, file);
      int type = lookup(idLexan);

      printf("The type code for %s is %d\n", idLexan, type);
      if (type == lookup(NOT_FOUND)) {
        // printf("Trying to insert into the symbol table\n");
        type = lookup(ID);
        set(symbolTable, idLexan, type);
        // printf("The lexan type is now=%d\n", lookup(ID));
        printf("The new type code for %s is %d\n", idLexan, type);
        return lookup(ID);
      }
      return type;
    } else if (ch == EOF) {
      return lookup(DONE);
    }
  } while (!feof(file));
  return ch;
}