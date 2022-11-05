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
        case IDENTIFICADOR:
        case ENTERO:
        case REAL:
            printf("Token: %s \t \t lexema: %s\n", token_names[t], yytext);
            break;
        // Nueva linea
        case NUEVA_LINEA:
            printf("Token: 'NL'\n");
            break;
        // Espacio
        case ESPACIO:
            break;
        
        case PALABRA_RESERVADA:
        case SIGNO_PUNTUACION:
        case FIN_CALCULADORA:
            if (yyleng == 1) {
                printf("Token: '%c'\n", yytext[0]);
            } else {
                printf("Token: %s\t\t\n", yytext);
            }
            break;
        
        // Errores
        default:
                printf("Error lexico: %s: %s\t\t\n", token_names[t],yytext);
            break;
        }
        
    };
    // Fin de archivo
    printf("Token: %s\n", token_names[t]);
    return 0;
}