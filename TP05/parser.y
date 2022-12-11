%code requires {
    #include "parser.h"
}

%code top{
#include <stdio.h>
#include <strings.h>
#include <math.h>
#include <string.h>
#include "scanner.h"
#include "calc.h"
}

%code provides {
    void yyerror(const char *);
    extern int yylexerrs;
    extern char errorBuf[100];
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

calculadora: listaDeSentencias FIN_CALCULADORA {clear_table(&symbol_table); return 0;}
    | FIN_CALCULADORA {clear_table(&symbol_table); return 0;}
    ;

listaDeSentencias : listaDeSentencias Sentencia 
    | Sentencia 
    ; 

Sentencia : Declaracion FDL {printf("\n");};
    | Expresion FDL {printf("%f\n\n", $1);}
    | error FDL {printf("\n");}
    | FDL
    ;
    
Declaracion : VAR IDENTIFICADOR                    {
                                                            if (!id_declared($2, symbol_table)) {
                                                                printf("%s: 0\n", $2);
                                                                declare_numeric_symbol($2, 0, VARIABLE, &symbol_table);
                                                            } else {
                                                                already_declared_error($2);
                                                            }
                                                            
                                                         }
    | VAR IDENTIFICADOR '=' Expresion                    {
                                                            if (!id_declared($2, symbol_table)) {
                                                                printf("%s: %f\n", $2, $4);
                                                                declare_numeric_symbol($2, $4, VARIABLE, &symbol_table);
                                                            } else {
                                                                already_declared_error($2);
                                                            }
                                                            
                                                         }
    | CTE IDENTIFICADOR '=' Expresion                    {
                                                            if (!id_declared($2, symbol_table)) {
                                                                printf("%s: %f\n", $2, $4);
                                                                declare_numeric_symbol($2, $4, CONSTANTE, &symbol_table);
                                                            } else {
                                                                already_declared_error($2);
                                                            }
                                                            
                                                         }
                                                        
Expresion : IDENTIFICADOR ASIGNACION_COMPUESTA Expresion {
                                                            if (id_declared($1, symbol_table)) {
                                                                if(get_entry_type($1, symbol_table) == VARIABLE) {
                                                                    compose_reassign_entry_value_double($1, $2, $3, &symbol_table);
                                                                    $$ = get_numeric_value($1, symbol_table);
                                                                } else {
                                                                    wrong_type_error($1, symbol_type_names[VARIABLE]);
                                                                    YYERROR;
                                                                }
                                                            } else {
                                                                undeclared_id_error($1);
                                                                YYERROR;
                                                            }
                                                         }
    | IDENTIFICADOR '=' Expresion                        {
                                                            if (id_declared($1, symbol_table)) {
                                                                if(get_entry_type($1, symbol_table) == VARIABLE) {
                                                                    reassign_entry_value_double($1, $3, &symbol_table);
                                                                    $$ = $3;
                                                                } else {
                                                                    wrong_type_error($1, symbol_type_names[VARIABLE]);
                                                                    YYERROR;
                                                                }
                                                            } else {
                                                                undeclared_id_error($1);
                                                                YYERROR;
                                                            }
                                                         }
    | IDENTIFICADOR                                      {
                                                            if (id_declared($1, symbol_table)) {
                                                                if (get_entry_type($1, symbol_table) != FUNCION) {
                                                                    $$ = get_numeric_value($1, symbol_table);
                                                                } else {
                                                                    char a_buffer[40];
                                                                    snprintf(a_buffer, sizeof(a_buffer),"%s o %s", symbol_type_names[VARIABLE], symbol_type_names[CONSTANTE]);
                                                                    wrong_type_error($1, "constante ni una variable");
                                                                    YYERROR;
                                                                }
                                                            } else {
                                                                undeclared_id_error($1);
                                                                YYERROR;
                                                            }
                                                         }    
    | NUM {$$ = $1;}
    | Expresion '+' Expresion {$$ = $1 + $3;}
    | Expresion '-' Expresion {$$ = $1 - $3;}
    | Expresion '*' Expresion {$$ = $1 * $3;}
    | Expresion '/' Expresion {$$ = $1 / $3;}
    | Expresion '^' Expresion {$$ = pow($1, $3);}
    | '-'Expresion %prec NEG {$$ = -$2;}
    | '('Expresion')' %prec PARENTHESIS {$$ = $2;}        
    | IDENTIFICADOR'('Expresion')' %prec FUNCTION {
                                                    if (id_declared($1, symbol_table)) {
                                                        if(get_entry_type($1, symbol_table) == FUNCION) {
                                                            double (*f)(double) = get_function($1, symbol_table);
                                                            $$ = f($3);
                                                        } else {
                                                            wrong_type_error($1, symbol_type_names[FUNCION]);
                                                            YYERROR;
                                                        }
                                                    } else {
                                                        undeclared_id_error($1);
                                                        YYERROR;
                                                    }
                                                  }
%%

void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}
