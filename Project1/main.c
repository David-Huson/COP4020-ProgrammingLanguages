#include "lexer.h"

int main(int argc, char* argv[]) {

  HashTable* symbolTable = init();
  dump(symbolTable);
  int* lineno = 0;
  FILE* input = fopen("test.txt", "r");
  int type = lexan(input, symbolTable, lineno);
  fclose(input);

  dump(symbolTable);
  destroy(symbolTable);
}
