#include <stdio.h>
#include "parser.h"
#include "calc.h"

int lexerrs = 0;
int main() {

	struct table_node* symbol_table = (struct table_node*) malloc(sizeof(struct table_node));

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