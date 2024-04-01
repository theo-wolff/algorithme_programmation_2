#define SIZE_WORD 30
#define NB_TAB 27 // Taille du tableau avec les 26 lettres de l'alphabet

typedef struct _node_dico
{
    char name[SIZE_WORD];
    struct _node_dico* next;
}node_dico;

typedef struct 
{
    node_dico** tab;
    int size_tab;
}table_dico;


void read_file_dico(char* name_file, table_dico* Table);
node_dico* create_node_dico(char new_name[SIZE_WORD]);
void insert_node_dico(table_dico *Table, node_dico *Node, int pos);
void disp_table_dico(table_dico* Table);
bool word_in_dico(table_dico* Table, char* word);
