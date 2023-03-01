/******************************************************************************
 * @file lexer.c
 * @author David Huson
 * @brief The lexical analyzer for project 1. Determines the type of each token
 * in a file.
 * @date 2023-01-21
 ******************************************************************************/
#include "lexer.h"
#include "symbolTable.h"

// declaring these here simulates encapsulation
int lineNumber;
int colNumber;
char* numLexan;
char* idLexan;

// initialize the lexical analyzer's variables, the symbol Table, and open the
// input file.
void initLexer(char* fileName, HashTable* table) {
  lineNumber = 1;
  colNumber = 1;
  symbolTable = table;
  // printf("file open = %d\n", file == NULL);
  file = fopen(fileName, "r");
}

// read the file character by character and determine the tokens and return
// their types
int lexan() {
  // char ch = fgetc(file);
  // printf("segfault check\n");
  // colNumber++;
  char ch = fgetc(file);
  colNumber++;
  do {
    // printf("segfault check\n");

    if (ch == ' ' || ch == '\t') {   // ignore whitespace other than newlines
                                     // (increment column number accordingly)
      ch = fgetc(file);
      colNumber++;
    } else if (ch == '\n') {   // ignore newlines and just increment the line
                               // number and reset the column number
      lineNumber++;
      colNumber = 0;
      ch = fgetc(file);
      colNumber++;
    } else if (ch == '~') {   // ignore everyting after the comment token until
                              // the next newline
      while (ch != '\n') {
        ch = fgetc(file);
      }
      colNumber = 0;
    } else if (isdigit(ch)) {   // if the character is a digit get the whole
      // number and return the correct type
      int numChars = 0;
      numLexan = malloc(sizeof(char*));
      while (isdigit(ch)) {
        colNumber++;
        numLexan = realloc(numLexan, ++numChars * sizeof(char));
        strncat(numLexan, &ch, numChars + 1);
        ch = fgetc(file);
      }

      ungetc(ch, file);
      colNumber--;
      return NUM;

    } else if (isalpha(ch)) {   // if the character is an alphabetical character
      int numChars = 0;
      int capacity = 256;
      idLexan = malloc(sizeof(char) * capacity);
      while ((isalnum(ch) || ch == '_' || ch == '.') && ch != '\n') {

        if (numChars == capacity - 1) {
          idLexan = realloc(idLexan, sizeof(char) * capacity);
        }

        if (ch == '_') {
          char nextChar = fgetc(file);
          if (nextChar == '_') {
            printf(
                "Syntax error on line %d, col %d. Identifiers cannot contain "
                "consecutive underscores.\n",
                lineNumber, colNumber);
            // free(idLexan);
            return DONE;
          }
          nextChar = ungetc(nextChar, file);
          colNumber--;
        }

        if (ch == '.') {
          char nextChar = fgetc(file);
          if (nextChar != '\n') {
            free(numLexan);
            free(idLexan);
            return DONE;
          }
        }
        idLexan[numChars++] = ch;
        ch = fgetc(file);
        colNumber++;
      }

      if (idLexan[strlen(idLexan) - 1] == '_') {
        printf("Syntax error on line %d, col %d. Identifiers cannot end with "
               "an underscore.\nFailure!\n",
               lineNumber, colNumber);
        free(idLexan);
        free(numLexan);
        exit(1);
        return DONE;
      }

      ungetc(ch, file);
      colNumber--;
      if (strcmp(idLexan, "int") == 0) {
        return INT;
      }

      if (strcmp(idLexan, "begin") == 0) {
        return BEGIN;
      }

      if (strcmp(idLexan, "end.") == 0) {
        return END;
      }

      int type = lookup(idLexan);

      if (type == NOT_FOUND) {

        type = ID;
        // set(symbolTable, idLexan, type);
      }
      // free(idLexan);
      return type;

    } else if (ch == EOF) {
      return DONE;
    } else {
      return ch;
    }
  } while (!feof(file));
  free(idLexan);
  free(numLexan);
  return DONE;
}

int getLineNum() { return lineNumber; }
int getColNum() { return colNumber; }
char* getNumLexeme() { return numLexan; }
char* getIdLexeme() { return idLexan; }