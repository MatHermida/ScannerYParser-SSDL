%option noyywrap

%{
#include <stdio.h>
#include <strings.h>
#include "parser.h"
char errorBuf[50];
%}

%option outfile="scanner.c"
%option header-file="scanner.h"
%option yylineno

letter [a-zA-Z]
digit [0-9]
nocero [1-9]
compassignmentop \+=|-=|\*=|[/]=
sign \+|\-
integer    {nocero}{digit}*  
exponentialpart [eE]{sign}?{integer}
operadores [/+*^-]
otros [^)*^/a-zA-Z0-9 \t\r\v\f\n(]

%%

\n                                                      {return '\n';}
[[:space:]]+                                            ;
salir                                                   {return FIN_CALCULADORA;}
sin|cos|tan|asin|acos|atan|sqrt|log                     {yylval.string = strdup(yytext); return FUNCION;}
var                                                     {yylval.string = strdup(yytext); return PALABRA_RESERVADA_VARIABLE;}
cte                                                     {yylval.string = strdup(yytext); return PALABRA_RESERVADA_CONSTANTE;}
{letter}({letter}|{digit})*{otros}({otros}|{letter}|{digit})*   {snprintf(errorBuf, sizeof(errorBuf),"Error léxico, identificador invalido, valor: %s", yytext);yyerror(errorBuf);}
{operadores}                                            {yylval.charac = yytext[0]; return yytext[0];}
=                                                       {yylval.charac = yytext[0]; return yytext[0];}
{compassignmentop}                                    {yylval.string = strdup(yytext); return ASIGNACION_COMPUESTA;}
[)(]                                                 {yylval.charac = yytext[0]; return yytext[0];}
{letter}({letter}|{digit})*                             {yylval.string = strdup(yytext); return IDENTIFICADOR;}
{integer}{letter}{integer}                              {snprintf(errorBuf, sizeof(errorBuf),"Error léxico, constante inválida, valor: %s", yytext);yyerror(errorBuf);}
{integer}                                               {yylval.num = atof(yytext); return NUM;}
({integer}?{letter}*\.{letter}*{digit}{letter}*{exponentialpart}?)({integer}?{letter}*\.{digit}{letter}*{exponentialpart}?)+                {snprintf(errorBuf, sizeof(errorBuf),"Error léxico, constante inválida, valor: %s", yytext);yyerror(errorBuf);}
({integer}{letter}*\.{letter}*{digit}?{letter}*{exponentialpart}?)({integer}{letter}*\.{digit}?{letter}*{exponentialpart}?)+                {snprintf(errorBuf, sizeof(errorBuf),"Error léxico, constante inválida, valor: %s", yytext);yyerror(errorBuf);}
{integer}\.{digit}*{exponentialpart}?                   |
{integer}?\.{digit}+{exponentialpart}?                  {yylval.num =  atof(yytext); return NUM;}
{otros}*                                                {snprintf(errorBuf, sizeof(errorBuf),"Error léxico, cadena desconocida, valor: %s", yytext);yyerror(errorBuf);}
