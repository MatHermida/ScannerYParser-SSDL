#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "calc.h"

/*
Sintaxis y Semantica de los Lenguajes
Grupo 02
Integrantes:
 - Juan Pablo Castiglione
 - Matias Kalomysky
 - Matias Hermida
 - Santiago Morel
*/

int main() {
	symbol_table = initial_table();
	// Habiamos pensado en hacer que la tabla de simbolos fuera una variable global para referenciarla
	// directamente en las funciones sin pasarla como parametro, pero, al mantenerla desacoplada de las funciones,
	// podriamos usar varias tablas si en un futuro se quisiera diferenciar namespaces.
	
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
