#include <stdbool.h>

struct table_entry {
    char *id;
    double value;
    char *type; // Constante, variable o funcion
};
struct table_node {
    struct table_entry data;
    struct table_node* next;
};
bool add_table_entry(struct table_entry, struct table_node *);