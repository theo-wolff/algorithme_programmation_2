#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dico.h"

void read_file_dico(char* name_file, table_dico* Table)
{
  /*en argument: nom du fichier, table de hachage 
                 contenant le dictionnaire français
    il s'agit d'une procédure modifiant directement la table de hachage
    voir rapport pour plus d'informations concernant la structure de la Table hachage
    Elle est équivalente à la table de hachage de mots_courants sans la fréquence d'apparition */

    FILE *file = fopen (name_file,"r");
    char name[SIZE_WORD];
    while(fscanf(file, "%s", name)==1)
    {
    int first_letter = name[0];
    int position = first_letter - 97;
    node_dico* new_node = create_node_dico(name);
    insert_node_dico(Table,new_node,position);
    }
    fclose(file);
}


node_dico* create_node_dico(char new_name[SIZE_WORD]) // Crée un noeud sans l'ajouter à la liste
{
  /*en argument: mot du dictiionnaire du noeud à ajouter dans la liste chaînée
    renvoie une structure de type node_dico contenant un nom du dictionnaire */

    node_dico* new = (node_dico*)malloc(sizeof(node_dico));
    strcpy(new->name,new_name); // Donner à new sa nouvelle valeur
    new->next = NULL;
    return new;
}



void insert_node_dico(table_dico *Table, node_dico *Node, int pos)
{
  /* en argument : Table de hachage pour le dictionnaire français, 
                   Noeud à ajouter dans la table
                   Position où ajouter le noeud i.e la première lettre (clé de table de hachage)
    Procédure modifiant directement la table du dictionnaire français*/

    Node->next = Table->tab[pos];
    Table->tab[pos] = Node;
 
}


void disp_table_dico(table_dico* Table) //table de hachage pour le dictionnaire français 
{
    /* en argument: Table de hachage du dictionnaire français
       Procédure affichant la table du dictionnaire français */
       
    for(int i=0;i<NB_TAB; i++)
    {
        node_dico* crt = Table->tab[i];
        printf("lettre %c:\n", i + 97);

        while(crt!=NULL)
        {
            printf("(%s); ", crt->name);
            crt = crt->next;
        }

        printf("\n\n\n\n\n\n\n");
    }
}


bool word_in_dico(table_dico* Table, char* word)
{
    /* en arguement : Table du dictionnaire français, mot à vérifier s'il est dans le dictionnaire français
       fonction renvoyant un booléen indiquant si le mot est présent ou non dans le dictionnaire français
       Si renvoie Faux, le mot est mal orthographié et il ne sera pas ajouté aux mots_courants */
    
    int first_letter = word[0] - 97;
    bool flag = false;
    node_dico *current=Table->tab[first_letter];
    while(current !=NULL && strcmp(word, current->name)!=0)
    {
    current = current->next;
    }
    if(current != NULL) //le mot est dans le dico fr
    {
    flag = true;
    }
    return flag;
}