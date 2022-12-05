%option noyywrap

%{
#include <stdio.h>
#include <strings.h>
#include "parser.h"
char errorBuf[100];
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
espacios [[:space:]]{-}[\n]

%%

;                                                       {yylval.charac = yytext[0]; return yytext[0];}
\n                                                      {yylval.charac = yytext[0]; return FDL;}
espacios+                                               ;
salir                                                   {return FIN_CALCULADORA;}
var                                                     {yylval.string = strdup(yytext); return VAR;}
cte                                                     {yylval.string = strdup(yytext); return CTE;}
{letter}({letter}|{digit})*{otros}({otros}|{letter}|{digit})*   {snprintf(errorBuf, sizeof(errorBuf),"Error léxico, identificador invalido, valor: %s\n", yytext);yyerror(errorBuf);}
{operadores}                                            {yylval.charac = yytext[0]; return yytext[0];}
=                                                       {yylval.charac = yytext[0]; return yytext[0];}
{compassignmentop}                                      {yylval.string = strdup(yytext); return ASIGNACION_COMPUESTA;}
[)(]                                                    {yylval.charac = yytext[0]; return yytext[0];}
{letter}({letter}|{digit})*                             {yylval.string = strdup(yytext); return IDENTIFICADOR;}
{integer}{letter}{integer}                              {snprintf(errorBuf, sizeof(errorBuf),"Error léxico, constante inválida, valor: %s\n", yytext);yyerror(errorBuf);}
{integer}                                               {yylval.num = atof(yytext); return NUM;}
({integer}?{letter}*\.{letter}*{digit}{letter}*{exponentialpart}?)({integer}?{letter}*\.{digit}{letter}*{exponentialpart}?)+                |
({integer}{letter}*\.{letter}*{digit}?{letter}*{exponentialpart}?)({integer}{letter}*\.{digit}?{letter}*{exponentialpart}?)+                {snprintf(errorBuf, sizeof(errorBuf),"Error léxico, constante inválida, valor: %s\n", yytext);yyerror(errorBuf);}
{integer}\.{digit}*{exponentialpart}?                   |
{integer}?\.{digit}+{exponentialpart}?                  {yylval.num =  atof(yytext); return NUM;}
{otros}*                                                {snprintf(errorBuf, sizeof(errorBuf),"Error léxico, cadena desconocida, valor: %s\n", yytext);yyerror(errorBuf);}
