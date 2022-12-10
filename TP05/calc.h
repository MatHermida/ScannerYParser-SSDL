#include <math.h>
#include <stdbool.h>
typedef enum symbol_type {VARIABLE, CONSTANTE, FUNCION} symbol_type;
extern char *symbol_type_names[3];
typedef struct table_entry {
    char id[512];
    union {
        double value;
        double (*function_pointer)(double);
    } data;
    symbol_type type; // Constante, variable o funcion
} table_entry;
typedef struct table_node {
    struct table_entry* data;
    struct table_node* next;
} table_node;

extern table_node * symbol_table;

bool id_declared(char*, struct table_node *);
symbol_type get_entry_type(char *, table_node *);
void add_table_entry(struct table_entry, struct table_node **);
void add_table_function_entry(struct table_entry, struct table_node **);
table_node * initial_table();
void clear_table(table_node **);
double get_numeric_value(char*, struct table_node*);
double (*get_function(char *, table_node*))(double);
void declare_numeric_symbol(char *, double, symbol_type, table_node **);
void reassign_entry_value_double(char *, double, struct table_node **);
void compose_reassign_entry_value_double(char *, char *, double, struct table_node **);
void already_declared_error(char *);
void undeclared_id_error(char *);
void wrong_type_error(char *, char *);
