#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "calc.h"

int main() {
	symbol_table = initial_table();
	
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