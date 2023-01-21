#include "symbolTable.h"

int main(int argc, char *argv[] ) {

    HashTable* symbolTable = init();
    print(symbolTable);
    destroy(symbolTable);

}
