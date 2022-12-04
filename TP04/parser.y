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

%start calculadora

%token <string> IDENTIFICADOR 
%token <num> NUM
%token CADENA_DESCONOCIDA 
%token CONSTANTE_INVALIDA 
%token IDENTIFICADOR_INVALIDO 
%right '='
%right <string> ASIGNACION_COMPUESTA
%left '+' '-'
%left '*' '/'
%precedence NEG
%right '^'
%precedence PARENTHESIS 
%precedence FUNCTION
%token FIN_CALCULADORA 
%token VAR
%token CTE
%token FDL

%type <num> Expresion

%%

calculadora: listaDeSentencias FIN_CALCULADORA {return 0;}
    | FIN_CALCULADORA {return 0;}
    ;

listaDeSentencias : listaDeSentencias Sentencia 
    | Sentencia 
    ; 

Sentencia : Declaracion FDL {printf("\n");};
    | Expresion FDL {printf("Expresion\n\n");}
    | error FDL {printf("\n");}
    | FDL
    ;
Declaracion : VAR IDENTIFICADOR {printf("Declarado '%s' como variable.\n", $2);}
    | VAR IDENTIFICADOR '=' Expresion {printf("Declarado '%s' como variable con valor inicial.\n", $2);}
    | CTE IDENTIFICADOR '=' Expresion {printf("Declarado '%s' como constante.\n", $2);}
    ;
Expresion : IDENTIFICADOR ASIGNACION_COMPUESTA Expresion {printf("Asignacion compuesta '%s'\n", $2);}
    | IDENTIFICADOR '=' Expresion {printf("Asignacion\n");}
    | IDENTIFICADOR {printf("Identificador\n");}    
    | NUM {printf("Numero\n");}
    | Expresion '+' Expresion {printf("Suma\n");}
    | Expresion '-' Expresion {printf("Resta\n");}
    | Expresion '*' Expresion {printf("Multiplicacion\n");}
    | Expresion '/' Expresion {printf("Division\n");}
    | Expresion '^' Expresion {printf("Potencia\n");}
    | '-'Expresion %prec NEG {printf("Cambio de signo\n");}
    | '('Expresion')' %prec PARENTHESIS {printf("Parentesis\n");}        
    | IDENTIFICADOR'('Expresion')' %prec FUNCTION {printf("Funcion\n");}
    ;
%%

void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}