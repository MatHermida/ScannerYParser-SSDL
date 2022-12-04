#include <stdio.h>
#include <ctype.h>
#include "tokens.h"
#include "scanner.h"

enum token t;
int yylex();
char *token_names[] = {"Fin de archivo", "Identificador", "Numero", "Palabra reservada", "NL", "Espacio", "Signo_puntuacion", "Cadena desconocida", "Fin calculadora", "Constante invalida", "Identificador invalido", "Signo asignacion", "Operador"};
// enum token {FDT, IDENTIFICADOR, ENTERO, REAL, PALABRA_RESERVADA, NUEVA_LINEA, ESPACIO, SIGNO_PUNTUACION, CADENA_DESCONOCIDA, FIN_CALCULADORA, CONSTANTE_INVALIDA, IDENTIFICADOR_INVALIDO, SIGNO_ASIGNACION, OPERADOR};


int main() {
    while (t = yylex()) {
        switch (t)
        {
        // Nueva linea
        case NUEVA_LINEA:
            printf("Token: 'NL'\n");
            break;
        // Espacio
        case ESPACIO:
            break;

        // Identificadores, enteros y reales
        case IDENTIFICADOR:
        case NUM:
            if (yyleng == 1) {
                printf("Token: %s \t \t lexema: %c\n", token_names[t], yytext[0]);
            } else {
                printf("Token: %s \t \t lexema: %s\n", token_names[t], yytext);
            }
            break;
        
        case PALABRA_RESERVADA:
        case SIGNO_PUNTUACION:
        case SIGNO_ASIGNACION:
        case OPERADOR:
        case FIN_CALCULADORA:
            if (yyleng == 1) {
                printf("Token: '%c'\n", yytext[0]);
            } else {
                printf("Token: %s\t\t\n", yytext);
            }
            break;
        
        // Errores
        case CADENA_DESCONOCIDA:
        case CONSTANTE_INVALIDA:
        case IDENTIFICADOR_INVALIDO:
                printf("Error lexico: %s: %s\t\t\n", token_names[t],yytext);
            break;
        }
        
    };
    // Fin de archivo
    printf("Token: %s\n", token_names[t]);
    return 0;
}