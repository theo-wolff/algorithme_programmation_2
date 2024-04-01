#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "code.h"


node* add_node(char new_name[SIZE_WORD], int new_freq) // Crée un noeud sans l'ajouter à la liste
{
    /* en argument : mot à ajouter dans le noeud, sa fréquence
       renvoie une structure de type node contenant un mot du fichier 
       "mots_courants.txt" et sa fréquence d'apparition */

    node* new = (node*)malloc(sizeof(node));
    strcpy(new->name,new_name); // Donner à new sa nouvelle valeur
    new->freq = new_freq;
    new->next = NULL;
    return new;
}



node* del_node(node* head)
{
    /* en argument : pointeur de type node 
       renvoie le second élement de la liste head et supprime le premier */

    if (head!= NULL)
    {
    node* new = head->next;
    free(head);
    return new;
    }
    printf("Trying to remove an element from an empty list.\n");
    return NULL;
}
















int size_list(node* head)
{
    /* en argument : pointeur de type node 
       renvoie le nombre d'éléments de la liste chaînée sur laquelle pointe head */
    int i = 0;
    while(head!=NULL)
    {
    head = head->next;
    i++;
    }
    return i;
}



void insert_node(table *Table, node *Node, int pos)
{
    /* en argument : table de hachage contenant les mots de "mots_courants.txt", Noeud à insérer,
       sa position i.e première lettre du mot présent dans Node 
       Procédure modifiant directement Table*/

    // L'insertion se fait par ordre alphabétique 

    node* prec = NULL;
    node* current = Table->tab[pos];
    while (current != NULL && strcmp(Node->name, current->name) > 0) // (>) on atteint le premier mot avec une comparaison parfaite
    {
        prec = current; 
        current = current->next;
    }

    if(current != NULL && strcmp(Node->name, current->name) == 0) // Si le nom est déjà présent dans la table, on augmente sa fréquence 
    {
        current->freq +=1;
    }
    else //sinon on rajoute un noeud à la liste au bon endroit 
    {
        if (prec == NULL) // si on est en début de liste 
        {
            // inserer en tete
            Node->next = Table->tab[pos];
            Table->tab[pos] = Node;
        }

        else
        {
            // inserer entre le compte trouve et son précedent
            prec->next = Node;
            Node->next = current;
        }
    }
}




void read_file(char* name_file, table* Table)
{
    /* en argument : nom du fichier "mots_courants.txt", table de hachage des mots courants 
       procédure modifiant directement la Table de hachage,
       voir rapport pour plus d'informations concernant la structure de la Table hachage */

    FILE *file = fopen (name_file,"r");
    char name[SIZE_WORD];
    while(fscanf(file, "%s", name)==1)
    {
    int first_letter = name[0];
    int position = first_letter - 97;
    node* new_node = add_node(name, 1);
    insert_node(Table,new_node,position);
    }
    fclose(file);
}



void disp_table(table* Table)
{
    /* en argument: Table de hachage de mots_courants
       Procédure affichant la table de mots_courants */

    for(int i=0;i<NB_TAB-1; i++)
    {
    node* crt = Table->tab[i];
    printf("lettre %c:\n", i + 97);

    while(crt!=NULL)
    {
        printf("(%s,%d); ", crt->name, crt->freq);
        crt = crt->next;
    }

    printf("\n\n");
    }
    node* crt = Table->tab[26];
    printf("acronymes:\n");
    while(crt!=NULL)
    {
        printf("(%s,%d); ", crt->name, crt->freq);
        crt = crt->next;
    }
    printf("\n\n");

}





node* prediction(char* input, table* Table, int* size)
{
    /* en argument : les premières lettres que l'on écrit pour la prédiction,
                     la table de hachage de mots_courants, 
                     la taille de la liste chaînée où travailler 
       renvoie un tableau avec tous les mots commençant par les lettres commençant dans input */

    int len = strlen(input);
    int first_letter = input[0]-97;
    int count = 0;
    node* head = Table->tab[first_letter];
    *size = size_list(head);
    node* result = (node*)malloc(*size*sizeof(node));
    for(int i=0;i<*size;i++)
    {
    if(head!=NULL)
    {
        char new_name[len];
        strncpy(new_name,head->name,len);
        
        if (strcmp(input,new_name)==0) //on ajoute dans result tous les mots commençants par input
        {
            strcpy(result[count].name,head->name);
            result[count].freq = head->freq;
            count++;
        }
        head = head->next;
    }

    }
    if(count == 0)//il y a aucun mots dans la liste mots courants commençant par input
    {
        strcpy(result[count].name,"1"); 
        
    }
    return result;
}




node* n_words(node* result, int* size, int n) //n de la prédiction 
{
    /* en argument : la liste contenant tous les mots commençants par input (les lettres écrites par l'utilisateur)
                     la taille de la liste chaînée commençant par la première lettre de input
                     le nombre de mots à prédire 
       renvoie un tableau contenant de taille n contenant les mots à afficher 
       si il y a moins de mots présent dans mots_courants que à afficher alors il y aura des doublons dans le tableau
       ces doublons seront traités dans la prochaine fonction   */

    node* new_result = (node*)malloc(n*sizeof(node));
    for(int j=0; j<n; j++)
    {
    int max = result[0].freq;
    int i_max = 0;
    for(int i=1; i<*size; i++)
    {
        if(result[i].freq>max)
        {
            max = result[i].freq;
            i_max = i;
        }
    }

    strcpy(new_result[j].name, result[i_max].name);
    result[i_max].freq = 0;
    }
    return new_result;
}


void disp_n_words(node* n_words, int n, char *start_name)
{
    /* en argument : La liste des mots commençant par les lettres écrites par l'utilisateur
                     Le nombre de mots à prédire 
                     Les premières lettres écrites par l'utilisateur 
       procédure affichant premièrement les mots dans mots courants commençant par start_name sans doublons
       Si le nombre affiché est inférieur au nombre souhaité, demande à l'utilisateur s'il veut ajouter les mots du dictionnaire français 
       Si oui, affiche les mots dans mots_courants et ceux du dictionnaire français commencant par les bonnes lettres*/

    if(strcmp(n_words[0].name, "1")!=0)
    {
        printf("\n(%s)\n", n_words[0].name);
    }
    int count = 1;

    int choice;
    bool flag = false;
    for(int i=1;i<n;i++)
    {
        for(int j=1; j<=i; j++)
        {
            if(strcmp(n_words[i-j].name, n_words[i].name)==0)
            {
                flag = true; //sors dès que on trouve deux fois le même mot 
            }
        }

        if(!flag)
        {
            printf("(%s)\n", n_words[i].name);
            count +=1;
        }
    }

    if(count!=n)
    {
        printf("\nNous n'avons pas trouvé le nombre souhaité de mots,\nVoulez vous les completer par les mots du dictionnaire français ? \n1: oui 2: non\n");
        scanf("%d",&choice);
        if(choice==1)
        {
            table_dico Table;
            Table.tab = (node_dico**)malloc(NB_TAB*sizeof(node_dico*));
            for(int i=0;i<NB_TAB;i++)
            {
                Table.tab[i]=NULL;
            }
            Table.size_tab=0; //nb premier

            read_file_dico("dico_fr.txt", &Table);
            
            node_dico *current=Table.tab[start_name[0]-97];
            int len = strlen(start_name);

            if(strcmp(n_words[0].name, "1")!=0)
            {
                printf("\n(%s)\n", n_words[0].name);
            }

            for(int i=1;i<n;i++)
            {
                for(int j=1; j<=i; j++)
                {
                    if(strcmp(n_words[i-j].name, n_words[i].name)==0)
                    {
                        flag = true; //traitement des doublons, sors dès que on trouve deux fois le même mot 
                    }
                }
                if(!flag)
                {
                    printf("(%s)\n", n_words[i].name);
                    count +=1;
                }
            }
            while(n-count>0)
            {

                if(current!=NULL)
                {
                    char *new_name=(char*)malloc(len*sizeof(char));
                    
                    strncpy(new_name,current->name,len); 
                    new_name[len]='\0'; 
                    bool flag2 = false;
                    

                    if(strcmp(new_name, start_name)==0) // traitement des doublons 
                    {
                        for(int i = 0; i<n; i++)
                        {
                            if(strcmp(current->name, n_words[i].name)==0)
                            {
                                flag2 = true; 
                            }
                        }
                        if(!flag2)
                        {
                            printf("(%s)\n", current->name);
                            count +=1;
                        }
                    }   
                    current = current->next;
                }
                else
                {
                    break;
                }
            }
        }
    }
}



void modif(table* Table, char* word, char* new_word)
{
    /* en argument : Table de hachage des mots_courants, le mot à modifier, le mot modifié
       procédure modifiant directement la table de hachage en remplaçant le mot voulu par new_word,
       si le mot voulu est bien dans mots_courants, sinon ne fait rien */

    int first_letter = word[0]-97;
    int done = 0;
    node* head = Table->tab[first_letter];
    int size = size_list(head);
    for(int i=0;i<size;i++)
    {
        if(head!=NULL)
        {
            if (strcmp(word,head->name)==0)
            {
                strcpy(head->name,new_word);
                done = 1;
            }
            head = head->next;
        }
    }

    if(done == 0)
    {
        printf("\nLe mot que vous souhaitez modifier n'est pas dans le dictionnaire des mots courants\n");
    }
}




void deleted(table* Table, char* word)
{
    /* en argument : Table de hachage des mots_courants, mot à supprimer 
       Procédure modifiant directement la table en supprimer le noeud contenant le mot word, 
       si le mot est présent dans la table, sinon ne fait rien */

    int first_letter = word[0] - 97;
    node *prec = NULL;
    node *current=Table->tab[first_letter];

    while(current != NULL && strcmp(current->name,word)!=0)
    {
        prec=current;
        current=current->next;
    }
    if(current != NULL)
    {
        if(prec==NULL)
        {
            Table->tab[first_letter]=Table->tab[first_letter]->next;
        }

        else
        {
            prec->next = current->next;
            free(current);
        }
        printf("\nle mot %s a été supprimé avec succès\n", word);
    }

    else
    {
        printf("\nLe mot que vous souhaitez supprimer n'est pas dans le dictionnaire des mots courants\n");
    }

}


void update(table *Table, char *word)
{
    /* en argument : Table de hachage des mots_courants, mot à mettre à jour
       procédure modifiant directement la Table 
       Test premièrement si le mot est correctement orthographié i.e conforme au dictionnaire français 
       Si le mot est déjà présent dans la table, augmente sa fréquence de 1, 
       sinon le rajoute à la bonne position */

    int first_letter = word[0] - 97;

    table_dico Table_dico;
    Table_dico.tab = (node_dico**)malloc(NB_TAB*sizeof(node_dico*));
    for(int i=0;i<NB_TAB;i++)
    {
        Table_dico.tab[i]=NULL;
    }
    Table_dico.size_tab=0; 
        
    read_file_dico("dico_fr.txt", &Table_dico);
    bool flag = word_in_dico(&Table_dico, word);

    node *prec = NULL;
    node *current=Table->tab[first_letter];


    if(flag==true)
    {  
        while(current != NULL && strcmp(current->name,word)!=0 )// lazy evaluation 
        {
            prec=current;
            current=current->next;
        }
        if(prec==NULL)
        {
            Table->tab[first_letter]->freq++;
        }

        else if(current!=NULL)
        {
            current->freq ++;
        }
        else 
        {
            node* new_node = add_node(word, 1);
            int pos = word[0]-97;
            insert_node(Table, new_node, pos);
        }
        printf("\nDictionnaire mis à jour avec succès !\n");
    }

    else 
    {
        printf("\nLe mot n'est pas conforme au dictionnaire !\n");
    }
}





void add_acro(table* Table, char* word) //on ajoute les accronymes dans la case Z
{
    /* en argument : Table de hachage mots_courants, acronyme à ajouter 
       procédure modifiant la table en ajoutant dans la dernière ligne du tableau l'acronyme */

    node* new = add_node(word, 1);
    insert_node(Table, new, 26);
}
//étant donné qu'ils sont en majuscule, et considérant la clé, on ne pourra pas les rechercher, uniquement les ajouter au dictionnaire


void menu(table* Table)
{
    /* en argument : la table de hachage mots_courants
       procédure permettant de dérouler le menu des choix */

    system("clear");
    bool leave = false;
    int choice;
    printf("\n\n\n***************************************************\n\n\n");
    printf("Bienvenue sur notre application de saisie intuitive");
    printf("\n\n\n***************************************************\n\n\n");
    while (!leave)
    {
        printf("\nIndiquez votre choix en écrivant le numéro correspondant:\n\n");
        printf("1  Prédiction\n");
        printf("2  Modifier un mot du dictionnaire\n");
        printf("3  Supprimer un mot du dictionnaire\n");
        printf("4  Ajout d'acronymes\n");
        printf("5  Voir le dictionnaire\n");
        printf("6  quitter\n");
        printf("\nChoix : ");
        scanf("%d", &choice);




        switch (choice)
        {
        case 1 :
            int n;
            int size = 0;
            char start_name[SIZE_WORD];
            char chosen_name[SIZE_WORD];
            printf("\nNombre de mots à prédire: ");
            scanf("%d", &n);
            printf("\nDébut du mot: ");
            scanf("%s", start_name);
            node* result = prediction(start_name,Table,&size);
            node* final_result = n_words(result,&size,n);
            //printf("%s", final_result[0].name);  
            disp_n_words(final_result,n,start_name);
            printf("Quel mot souhaitez-vous écrire ?\n");
            scanf("%s", &chosen_name);
            update(Table, chosen_name);
            break;

        case 2 :
            char word[SIZE_WORD];
            char new_word[SIZE_WORD];
            printf("Mot à modifier : \n");
            scanf("%s", word);
            printf("Nouveau mot : \n");
            scanf("%s", new_word);
            modif(Table,word,new_word);
            break;

        case 3 :
            char word2[SIZE_WORD];
            printf("Quel mot souhaitez-vous supprimer ?\n");
            scanf("%s", word2);
            deleted(Table, word2);  
            break;

        case 4 :
            char word3[SIZE_WORD];
            printf("Quel acronyme souhaitez-vous ajouter ?\n");
            scanf("%s",word3);
            add_acro(Table, word3);
            printf("\nl'acronyme a été ajoutée avec succès\n");
            break;

        case 5 :
            printf("\n\n");
            printf("Le format du dictionnaire est le suivant : (mot, fréquence d'apparition du mot)\n\n");
            disp_table(Table); 
            break;

        case 6 :
            leave = true;
            break;

        default :
            printf("Incorrect choice\n");
            break;
        }
    }
}


























