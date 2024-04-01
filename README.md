# algorithme_programmation_2

## 

README.md

# Projet d'Algorithmique et Programmation II - WOLFF & PENOT

Le sujet est basé sur la saisie intuitive ou prédictive. L'objectif est d'entrer une série de caractères et que le programme propose n mots commençant par cette série. Le dictionnaire est mis à jour à chaque recherche, et on a la possibilité d'ajouter, modifier ou supprimer un mot du dictionnaire.

## Pré-requis

### Commandes
Ce qu'il est requis pour commencer avec notre projet...

- main.c
- code.c
- code.h
- dico.c
- dico.h
- makefile
- mots_courants.txt
- dico_fr.txt

### Contenus

Le fichier texte mots_courants.txt contient le dictionnaire de mots recherchés, que l'on met à jour à chaque mot entré. Tandis que le fichier texte dic.txt contient la liste des mots du dictionnaire français sans caractères spéciaux.

Nous avons créé deux fichiers headers :
- code.h qui rassemble les fonctions de prédiction et de mise à jour du dictionnaire de mots courants.
- dico.h qui contient les fonctions supplémentaires vérifiant l'orthographe et qui complètent le dictionnaire de mots courants.

## Démarrage

Executez les commandes:
```
>>> make main
>>> ./main
```

Un texte de ce type s'affichera : 
```
1  Prédiction
2  Modifier un mot du dictionnaire
3  Supprimer un mot du dictionnaire  
4  Voir le dictionnaire
5  quitter
Choix :
```

## Auteurs
Liste des auteurs du projet :
* **Théo Wolff** 
* **Marie Penot**

Le projet a entièrement été réalisé sans autres contributeurs.
