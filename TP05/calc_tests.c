#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

void print_table(table_node * table) {
    table_node * current = table;
    
    while (current != NULL)
    {
        table_entry * data = current -> data;
        if (data -> type == FUNCION) {
            printf("Funcion %s\n", data -> id);
        } else {
            printf("ID: %s, VALOR: %f, TIPO: %s\n", data->id, data->value, symbol_type_names[data->type]);
        }
        
        current = current -> next;
    }
    
}

int main() {
    
    table_node * symbol_table = initial_table();
    
    // struct table_entry buffer[] = {
    //     [0].id = "sin",
    //     [0].type = FUNCION,
    //     [1].id = "cos",
    //     [1].type = FUNCION,
    //     [2].id = "tan",
    //     [2].type = FUNCION,
    //     [3].id = "asin",
    //     [3].type = FUNCION,
    //     [4].id = "acos",
    //     [4].type = FUNCION,
    //     [5].id = "atan",
    //     [5].type = FUNCION,
    //     [6].id = "sqrt",
    //     [6].type = FUNCION,
    //     [7].id = "log",
    //     [7].type = FUNCION,
    //     [8].id = "e",
    //     [8].value = M_E,
    //     [8].type = CONSTANTE,
    //     [9].id = "pi",
    //     [9].value = M_PI,
    //     [9].type = CONSTANTE,
    // };
    
    // for (int i = 0; i < 10; i++)
    // {
    //     add_table_entry(buffer[i], &symbol_table);
    // }

    double (*seno)(double) = (get_function("sin", symbol_table));
    printf("%f\n", (*seno)(M_PI/2));
    printf("%f\n", (*seno)(M_PI));
    //print_table(symbol_table);
    // printf("%f\n", get_numeric_value("e", symbol_table));
    // printf("%f\n", get_numeric_value("pi", symbol_table));
}