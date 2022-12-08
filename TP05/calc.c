#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "parser.h"
#include "calc.h"

char *symbol_type_names[] = {"Variable", "Constante", "Funcion"};
double pi = M_PI;
double e = M_E;

bool id_declared(char* id, table_node * table) {
    table_node * current = table;
    
    while (current != NULL && strcmp(current -> data -> id, id))
    {
        current = current -> next;
    }
    if (current) {
        return true;
    } else {
        return false;
    }
}

symbol_type get_entry_type(char * id, table_node * table) {
    table_node * current = table;
    
    while (current != NULL && strcmp(current -> data -> id, id))
    {
        current = current -> next;
    }
    return current -> data-> type;
}

void add_table_entry(table_entry new_entry, struct table_node ** table) {
    table_node * new_node = malloc(sizeof(table_node));
    new_node -> data = malloc(sizeof(table_entry));
    strcpy(new_node -> data -> id, new_entry.id);
    new_node -> data -> type = new_entry.type;
    new_node -> data -> value = new_entry.value;
    
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
        [0].value = &sin,
        [0].type = FUNCION,
        [1].id = "cos",
        [1].value = &cos,
        [1].type = FUNCION,
        [2].id = "tan",
        [2].value = &tan,
        [2].type = FUNCION,
        [3].id = "asin",
        [3].value = &asin,
        [3].type = FUNCION,
        [4].id = "acos",
        [4].value = &acos,
        [4].type = FUNCION,
        [5].id = "atan",
        [5].value = &atan,
        [5].type = FUNCION,
        [6].id = "sqrt",
        [6].value = &sqrt,
        [6].type = FUNCION,
        [7].id = "log",
        [7].value = &log10,
        [7].type = FUNCION,
        [8].id = "e",
        [8].value = &e,
        [8].type = CONSTANTE,
        [9].id = "pi",
        [9].value = &pi,
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
    double * num = (double *)(table_pointer -> data -> value);
    return *num;
};

double (*get_function(char * function_id, table_node* table))(double) {
    table_node * table_pointer = table;
    while (table_pointer -> next != NULL && strcmp(table_pointer -> data -> id, function_id))
    {
        table_pointer = table_pointer -> next;
    }
    double (*function_ptr)(double) = (double (*)(double)) table_pointer -> data -> value;
    return function_ptr;
};

void declare_numeric_symbol(char * id, double value, symbol_type type , table_node ** table) {
    table_entry new_entry = {.value=&value, .type=type};
    strcpy(new_entry.id, id);
    add_table_entry(new_entry, table);
}