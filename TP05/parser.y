    %code top{
#include <stdio.h>
#include <strings.h>
#include <math.h>
#include "scanner.h"
#include "calc.h"

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
    | Expresion FDL {printf("%f\n\n", $1);}
    | error FDL {printf("\n");}
    | FDL
    ;
Declaracion : VAR IDENTIFICADOR {YYERROR;}
    | VAR IDENTIFICADOR '=' Expresion {declare_numeric_symbol($2, $4, VARIABLE, &symbol_table);}
    | CTE IDENTIFICADOR '=' Expresion {printf("Declarado '%s' como constante.\n", $2);}
    ;
Expresion : IDENTIFICADOR ASIGNACION_COMPUESTA Expresion {printf("Asignacion compuesta '%s'\n", $2);}
    | IDENTIFICADOR '=' Expresion {printf("Asignacion\n");}
    | IDENTIFICADOR {$$ = get_numeric_value($1, symbol_table);}    
    | NUM {$$ = $1;}
    | Expresion '+' Expresion {$$ = $1 + $3;}
    | Expresion '-' Expresion {$$ = $1 - $3;}
    | Expresion '*' Expresion {$$ = $1 * $3;}
    | Expresion '/' Expresion {$$ = $1 / $3;}
    | Expresion '^' Expresion {$$ = pow($1, $3);}
    | '-'Expresion %prec NEG {$$ = -$2;}
    | '('Expresion')' %prec PARENTHESIS {$$ = $2;}        
    | IDENTIFICADOR'('Expresion')' %prec FUNCTION {$$ = (*get_function)($1, symbol_table)($3);}
    ;
%%

void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}