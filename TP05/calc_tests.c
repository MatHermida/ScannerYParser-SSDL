#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

void print_table(struct table_node* table) {
    struct table_node* table_pointer = table;
    
    while (table_pointer != NULL)
    {
        struct table_entry data = table_pointer -> data;

        if (data.type == "Funcion") {
            printf("Funcion %s\n", data.id);
        } else {
            printf("ID: %s, VALOR: %f, TIPO: %s\n", data.id, data.value, data.type);
        }
        
        table_pointer = table_pointer -> next;
    }
    
}

int main() {
    struct table_node* symbol_table = (struct table_node*) malloc(sizeof(struct table_node));
    struct table_entry buffer[] = {
        [0].id = "sin",
        [0].type = "Funcion",
        [1].id = "cos",
        [1].type = "Funcion",
        [2].id = "tan",
        [2].type = "Funcion",
        [3].id = "asin",
        [3].type = "Funcion",
        [4].id = "acos",
        [4].type = "Funcion",
        [5].id = "atan",
        [5].type = "Funcion",
        [6].id = "sqrt",
        [6].type = "Funcion",
        [7].id = "log",
        [7].type = "Funcion",
        [8].id = "e",
        [8].value = M_E,
        [8].type = "Constante",
        [9].id = "pi",
        [9].value = M_PI,
        [9].type = "Constante",
        [10].id = "pi",
        [10].value = 1,
        [10].type = "Constante",
        [11].id = "cosa",
        [11].type = "Variable"
    };
    
    for (int i = 0; i < 12; i++) {
        add_table_entry(buffer[i], symbol_table);
    }

    print_table(symbol_table);
}