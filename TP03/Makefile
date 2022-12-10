main: main.c scanner.c
	gcc -g -Wall scanner.c main.c -o main -lfl

scanner.c scanner.h: scanner.l
	flex scanner.l

clean:
	rm scanner.c scanner.h
