main: main.o scanner.o parser.o
	gcc main.o scanner.o parser.o -o main -lfl

main.o: main.c scanner.c parser.c
	gcc -c main.c

scanner.o: scanner.c parser.h
	gcc -c scanner.c

parser.o: parser.c scanner.h
	gcc -c parser.c

scanner.c scanner.h: scanner.l
	flex scanner.l

parser.c parser.h: parser.y
	bison parser.y

clean:
	rm parser.c scanner.c scanner.h parser.h parser.o scanner.o main.o