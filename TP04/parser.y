%code top{
#include <stdio.h>
#include <strings.h>
#include "scanner.h"
}

%code provides {
    void yyerror(const char *);
    extern int yylexerrs;
}

%defines "parser.h"
%output "parser.c"
%define parse.error verbose

%union {
    double num;
    char* string;
    char charac;
}

%token <string> IDENTIFICADOR 
%token PALABRA_RESERVADA_VARIABLE "var"
%token PALABRA_RESERVADA_CONSTANTE "cte"
%token NUM
%token CADENA_DESCONOCIDA 
%token CONSTANTE_INVALIDA 
%token IDENTIFICADOR_INVALIDO 
%right '='
%right ASIGNACION_COMPUESTA
%left '+' '-'
%left '*' '/'
%left NEG
%left '^'
%token FUNCION
%token FIN_CALCULADORA 


%%

calculadora : listaDeSentencias FIN_CALCULADORA {return 0;}
    | FIN_CALCULADORA {return 0;}
    ;
listaDeSentencias : listaDeSentencias Sentencia
    | Sentencia
    ;
Sentencia : Declaracion
    | IDENTIFICADOR
    | Expresion
    ;
Declaracion : "var" IDENTIFICADOR {printf("Define '%s' como variable\n", $2);}
    | "var" IDENTIFICADOR '=' Expresion
    | "cte" IDENTIFICADOR '=' Expresion
    ;
Expresion : IDENTIFICADOR ASIGNACION_COMPUESTA Expresion
    | IDENTIFICADOR '=' Expresion
    | Expresion '+' Expresion
    | Expresion '-' Expresion
    | Expresion '*' Expresion
    | Expresion '/' Expresion

    | FUNCION'('Expresion')'
    | NUM
    ;


%%

void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}