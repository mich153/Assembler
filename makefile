all: assembler

assembler: assembler.o line.o symbol.o keyword.o commandLine.o guidanceLine.o memoryCommand.o outPut.o
	gcc -ansi -Wall -pedantic -o assembler assembler.o line.o symbol.o keyword.o commandLine.o guidanceLine.o memoryCommand.o outPut.o

assembler.o: assembler.c assembler.h line.h commandLine.h guidanceLine.h keyword.h symbol.h memoryCommand.h outPut.h
	gcc -ansi -Wall -pedantic -c assembler.c

line.o: line.c line.h keyword.h symbol.h commandLine.h guidanceLine.h
	gcc -ansi -Wall -pedantic -c line.c

symbol.o: symbol.c symbol.h line.h keyword.h commandLine.h
	gcc -ansi -Wall -pedantic -c symbol.c

keyword.o: keyword.c keyword.h
	gcc -ansi -Wall -pedantic -c keyword.c

commandLine.o: commandLine.c commandLine.h line.h symbol.h keyword.h memoryCommand.h
	gcc -ansi -Wall -pedantic -c commandLine.c

guidanceLine.o:	guidanceLine.c guidanceLine.h keyword.h line.h symbol.h
	gcc -ansi -Wall -pedantic -c guidanceLine.c

memoryCommand.o: memoryCommand.c memoryCommand.h symbol.h keyword.h line.h commandLine.h
	gcc -ansi -Wall -pedantic -c memoryCommand.c

outPut.o: outPut.c outPut.h assembler.h guidanceLine.h keyword.h line.h memoryCommand.h symbol.h commandLine.h
	gcc -ansi -Wall -pedantic -c outPut.c

clean:
	rm *.o assembler
