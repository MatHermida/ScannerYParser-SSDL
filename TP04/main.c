#include <stdio.h>
#include "parser.h"

int lexerrs = 0;
int main() {
	switch( yyparse() ){
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		puts("Memoria insuficiente"); return 2;
	}
	return 0;
}