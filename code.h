#include "dico.h"

typedef struct _node
{
    char name[SIZE_WORD];
    int freq;
    struct _node* next;
}node;

typedef struct
{
    node** tab;
    int size_tab; // Nombre de mots dans le dictionnaire
}table;





node* add_node(char new_name[SIZE_WORD], int new_freq);
node* del_node(node* head);
int size_list(node* head);
void read_file(char* name_file, table* Table);
void insert_node(table *Table, node *node, int pos);
void disp_table(table *Table);
node* prediction(char* input, table* Table, int* size);
node* n_words(node* result, int* size, int n);
void modif(table* Table, char* word, char* new_word);
void deleted(table* Table, char* word);
void update(table *Table, char *word);
void menu(table* Table);
void disp_n_words(node* n_words, int n, char *start_name);
void add_acro(table* Table, char* word);



