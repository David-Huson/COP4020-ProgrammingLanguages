C = gcc
main: main.o hashTable.o lexer.o symbolTable.o parse.o
	$(C)  -o $@ $^

clean:
	rm -rf *.dSYM *.o *.gc* main lexer hashTable symbolTable 
