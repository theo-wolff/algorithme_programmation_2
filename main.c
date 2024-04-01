#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "code.h"




int main()
{
   //initialisation
   table Table;
   Table.tab = (node**)malloc(NB_TAB*sizeof(node*));
   for(int i=0;i<NB_TAB;i++)
   {
    Table.tab[i]=NULL;
   }
   Table.size_tab=0; //nb premier
  
    read_file("mots_courants.txt", &Table);
    //disp_table_dico(&Table);
    menu(&Table);


    return 0;
}















