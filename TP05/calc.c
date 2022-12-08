#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "parser.h"
#include "calc.h"

char *symbol_type_names[] = {"Variable", "Constante", "Funcion"};


// bool id_available(char* id, struct table_node * table) {
//     struct table_node * table_pointer = table;
    
//     while (table_pointer != NULL)
//     {
//         if (table_pointer -> data.id == id){
//             return false;
//         }
//         table_pointer = table_pointer -> next;
//     }
//     return true;
// }

void add_table_entry(table_entry new_entry, struct table_node ** table) {
    table_node * new_node = malloc(sizeof(table_node));
    new_node -> data = malloc(sizeof(table_entry));
    strcpy(new_node -> data -> id, new_entry.id);
    new_node -> data -> type = new_entry.type;
    if (new_entry.type == FUNCION) {
        new_node -> data -> function_pointer = new_entry.function_pointer;
    } else {
        new_node -> data -> value = new_entry.value;
    }
    new_node -> next = NULL;
    
    if (*table) {
        table_node * current = *table;
        while (current -> next != NULL)
        {
            current = current -> next;
        }
        current -> next = new_node;
        current -> next -> next = NULL;
    } else {
        *table = new_node;
    }
}

table_node * initial_table() {
    table_node * table = NULL;
    table_entry initial_symbols[] = {
        [0].id = "sin",
        [0].function_pointer = &sin,
        [0].type = FUNCION,
        [1].id = "cos",
        [1].function_pointer = &cos,
        [1].type = FUNCION,
        [2].id = "tan",
        [2].function_pointer = &tan,
        [2].type = FUNCION,
        [3].id = "asin",
        [3].function_pointer = &asin,
        [3].type = FUNCION,
        [4].id = "acos",
        [4].function_pointer = &acos,
        [4].type = FUNCION,
        [5].id = "atan",
        [5].function_pointer = &atan,
        [5].type = FUNCION,
        [6].id = "sqrt",
        [6].function_pointer = &sqrt,
        [6].type = FUNCION,
        [7].id = "log",
        [7].function_pointer = &log10,
        [7].type = FUNCION,
        [8].id = "e",
        [8].value = M_E,
        [8].type = CONSTANTE,
        [9].id = "pi",
        [9].value = M_PI,
        [9].type = CONSTANTE,
    };
    for (int i = 0; i < 10; i++)
    {
        add_table_entry(initial_symbols[i], &table);
    }

    return table;
}

double get_numeric_value(char* id, struct table_node* table) {
    table_node * table_pointer = table;
    while (table_pointer -> next != NULL && strcmp(table_pointer -> data -> id, id))
    {
        table_pointer = table_pointer -> next;
    }

    return table_pointer -> data -> value;
};

double (*get_function(char * function_id, table_node* table))(double) {
    table_node * table_pointer = table;
    while (table_pointer -> next != NULL && strcmp(table_pointer -> data -> id, function_id))
    {
        table_pointer = table_pointer -> next;
    }

    return table_pointer -> data -> function_pointer;
};

void declare_numeric_symbol(char * id, double value, symbol_type type , table_node ** table) {
    table_entry new_entry = {.value=value, .type=type};
    strcpy(new_entry.id, id);
    add_table_entry(new_entry, table);
}