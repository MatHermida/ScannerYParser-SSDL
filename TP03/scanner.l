%option noyywrap

%{
#include <stdio.h>
#include <strings.h>
#include "tokens.h"
%}

%option outfile="scanner.c"
%option header-file="scanner.h"

letter [a-zA-Z]
digit [0-9]
nocero [1-9]
compassignmentop \+=|-=|\*=|[/]=
sign \+|\-
integer    {nocero}{digit}*  
exponentialpart [eE]{sign}?{integer}
espacio [ \t\r\v\f]
operadores [/+*^-]
otros [^)*^/a-zA-Z0-9 \t\r\v\f\n(]

%%

{espacio}                                               {return ESPACIO;}
\n                                                      {return NUEVA_LINEA;}
salir                                                   {return FIN_CALCULADORA;}
var|cte                                                 {return PALABRA_RESERVADA;}
{letter}({letter}|{digit})*{otros}({otros}|{letter}|{digit})*   {return IDENTIFICADOR_INVALIDO;}
{operadores}                                            {return OPERADOR;}
{compassignmentop}|=                                    {return SIGNO_ASIGNACION;}
[)*^/(]                                                 {return SIGNO_PUNTUACION;}
{letter}({letter}|{digit})*                             {return IDENTIFICADOR;}
{integer}{letter}{integer}                              {return CONSTANTE_INVALIDA;}
{integer}                                               {return ENTERO;}
({integer}?{letter}*\.{letter}*{digit}{letter}*{exponentialpart}?)({integer}?{letter}*\.{digit}{letter}*{exponentialpart}?)+                {return CONSTANTE_INVALIDA;}
({integer}{letter}*\.{letter}*{digit}?{letter}*{exponentialpart}?)({integer}{letter}*\.{digit}?{letter}*{exponentialpart}?)+                {return CONSTANTE_INVALIDA;}
{integer}\.{digit}*{exponentialpart}?                   |
{integer}?\.{digit}+{exponentialpart}?                  {return REAL;}
{otros}*                                                {return CADENA_DESCONOCIDA;}
