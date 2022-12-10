#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

// ARCHIVO SOLAMENTE USADO PARA TESTEOS RAPIDOS

void print_table(table_node * table) {
    table_node * current = table;
    // Iterate over the linked list of table nodes
    while (current != NULL)
    {
        // Get the data field of the current table node
        table_entry * data = current->data;
        // Check if the type field of the table_entry is FUNCTION
        if (data->type == FUNCION) {
            // If it is, print the function id
            printf("Funcion %s\n", data->id);
        } else {
            // Otherwise, print the id, value, and type of the table_entry
            printf("ID: %s, VALOR: %f, TIPO: %s\n", data->id, data->data.value, symbol_type_names[data->type]);
        }
        // Advance to the next table node
        current = current->next;
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
    seno(3.14);
    seno(3.14/2);
    print_table(symbol_table);
    clear_table(&symbol_table);
    print_table(symbol_table);
}
