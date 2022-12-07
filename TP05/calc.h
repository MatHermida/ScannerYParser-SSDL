

typedef enum symbol_type {VARIABLE, CONSTANTE, FUNCION} symbol_type;
char *symbol_type_names[3];
typedef struct table_entry {
    char id[512];
    double value;
    symbol_type type; // Constante, variable o funcion
} table_entry;
typedef struct table_node {
    struct table_entry* data;
    struct table_node* next;
} table_node;
table_node * symbol_table;
void add_table_entry(struct table_entry, struct table_node **);
double get_numeric_value(char*, struct table_node*);
table_node * initial_table();