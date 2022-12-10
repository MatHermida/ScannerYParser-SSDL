main: calc.o main.o scanner.o parser.o
	gcc calc.o main.o scanner.o parser.o -o main -lfl -lm

main.o: main.c scanner.c parser.c calc.c
	gcc -c main.c

calc.o: calc.c parser.h
	gcc -c calc.c

scanner.o: scanner.c parser.h
	gcc -c scanner.c

parser.o: parser.c scanner.h
	gcc -c parser.c

scanner.c scanner.h: scanner.l
	flex scanner.l

parser.c parser.h: parser.y
	bison parser.y

clean:
	rm parser.c parser.h parser.o scanner.c scanner.h scanner.o main.o calc.o
