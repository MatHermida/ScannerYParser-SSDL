#include <stdio.h>
#include <ctype.h>
#include "tokens.h"

enum token t;
int yylex();
char *token_names[] = {"Fin de archivo", "Identificador", "Entero", "Real", "Palabra reservada", "NL", "Espacio", "Signo_puntuacion", "Cadena desconocida", "Fin calculadora", "Constante invalida"};
// enum token {FDT, IDENTIFICADOR, ENTERO, REAL, PALABRA_RESERVADA, NUEVA_LINEA, ESPACIO, SIGNO_PUNTUACION, CADENA_DESCONOCIDA, FIN_CALCULADORA};
char *yytext;
int yyleng;

int main() {
    while (t = yylex()) {
        switch (t)
        {
        // Identificadores, enteros y reales
        case 1:
        case 2:
        case 3:
            printf("Token: %s \t \t lexema: %s\n", token_names[t], yytext);
            break;
        // Nueva linea
        case 5:
            printf("Token: 'NL'\n");
            break;
        // Espacio
        case 6:
            break;
        
        case 4:
        case 7:
        case 9:
            if (yyleng == 1) {
                printf("Token: '%c'\n", yytext[0]);
            } else {
                printf("Token: %s\t\t\n", yytext);
            }
            break;
        
        
        default:
                printf("Error lexico: %s: %s\t\t\n", token_names[t],yytext);
            break;
        }
        
    };
    printf("Token: fin de archivo\n");
    return 0;
}