#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "parser.h"
#include "calc.h"

bool id_available(char* id, struct table_node * table) {
    struct table_node * table_pointer = table;
    
    while (table_pointer != NULL)
    {
        if (table_pointer -> data.id == id){
            return false;
        }
        table_pointer = table_pointer -> next;
    }

    return true;
    
}

bool add_table_entry(struct table_entry new_entry, struct table_node * table) {
    if (id_available(new_entry.id, table))
    {
        struct table_node * table_pointer = table;
        while (table_pointer -> next != NULL)
        {
            table_pointer = table_pointer -> next;
        }
        table_pointer -> next = (struct table_node *)malloc(sizeof(struct table_node));
        table_pointer = table_pointer -> next;
        table_pointer -> data = new_entry;
        table_pointer -> next = NULL;
        
        return true;
    }
    printf("No se puede redeclarar una constante\n");
    return false;
}
