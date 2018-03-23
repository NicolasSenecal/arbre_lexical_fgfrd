/*
 * Lexique.c (main)
 * Programme construisant le lexique d'un texte contenu dans un fichier fournit 
 * comme argument de la ligne de commande, avec différentes options et fonctionnalités
 * 
 * Auteur : Myriam ANIK et Nicolas SENECAL
 * IMAC1 - TD01 - Promotion 2020
 * Date : 26/03/2018
 */

#include "ui.h"

int main(int argc, char *argv[]) {

  if (argc == 1) {/* Aucune commandes */
    printf("Usage : ./Lexique [-l] [-r <Mot>] [-s] [-S] [-d] nomFichier\n");
    return 0;
  }

  int i;
  char cmd;
  char *nomFichier = argv[argc - 1];

  Arbre a = NULL;
  if (cmdGenererArbre(&a, nomFichier) == 0) {
    return 0;
  }
  
  for (i = 1; i < argc - 1; i++) {
    if (*argv[i] == '-') {
      cmd = *(argv[i] + 1); /* Pointeur sur l'adresse du caractère suivant de argv[i] */
      if (i + 1 >= argc) /* si aucun mot n'est indiqué après la commande */
        switchCmdLettre(&a, nomFichier, cmd, NULL);
      else
        switchCmdLettre(&a, nomFichier, cmd, (unsigned char*) argv[++i]);
    }
  }

  freeArbre(a);

  return 0;
}