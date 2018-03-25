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
  int i;
  char cmd[MAX_CHAR] = "";
  char nomFichier[MAX_CHAR] = "";
  Arbre a = NULL;

  if (argc > 1) { /* L'utilisateur a rentré dès commandes */
    strcpy(nomFichier, argv[argc - 1]);
  }


  if (strcmp(argv[argc - 1], "-h") != 0) {
    while (nomFichier[0] == '\0' || nomFichier[0] == '-' || cmdGenererArbre(&a, nomFichier) == 0) {
      printf("Veuillez entrez le nom du fichier a lire (ou 0 pour quitter) : ");
      scanf(" %51s", cmd);
      if (cmd[0] == '0')
        return 0;
      strcpy(nomFichier, cmd);
    }

    /* S'il n'y a pas d'options (vide ou seulement le nom du ficher), on affiche le menu */
    if (argc == 1 || (argc == 2 && *argv[1] != '-')) {
      printMenu();
      while (printf("==> ") && scanf(" %c", &(cmd[0])) && cmd[0] != '0' && cmd[0] != 'q' && cmd[0] != 'Q') {
        if (cmd[0] == 'h')
          printMenu();
        else
          switchCmdLettre(&a, nomFichier, cmd[0], NULL);
      }
    } else {
      for (i = 1; i < argc; i++) {
        if (*argv[i] == '-') {
          cmd[0] = *(argv[i] + 1); /* Pointeur sur l'adresse du caractère suivant de argv[i] */
          if (i + 1 >= argc - 1) /* si aucun mot n'est indiqué après la commande */
            switchCmdLettre(&a, nomFichier, cmd[0], NULL);
          else
            switchCmdLettre(&a, nomFichier, cmd[0], (unsigned char*) argv[++i]);
        }
      }
    }
    freeArbre(a);
  } else {
    printHelp();
  }

  return 0;

}
