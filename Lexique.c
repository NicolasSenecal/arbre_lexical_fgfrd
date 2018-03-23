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

  if (argc == 1) {/* Aucune commandes */
    printf("Usage : ./Lexique [-l] [-r <Mot>] [-s] [-S] [-d] nomFichier\n");
    printf("Tapez ./Lexique -h pour l'aide \n");
  } else {
    strcpy(nomFichier, argv[argc - 1]);
  }

printf("%s\n", argv[argc-1]);
  

 if(strcmp(argv[argc-1],"-h")!=0){
  while (cmdGenererArbre(&a, nomFichier) == 0) {
    printf("Veuillez entrez un nom de fichier valide (ou 0 pour quitter) : ");
    scanf(" %51s", cmd);
    if (cmd[0] == '0')
      return 0;

    strcpy(nomFichier, cmd);
  }

  for (i = 1; i < argc - 1; i++) {
    if (*argv[i] == '-') {
      cmd[0] = *(argv[i] + 1); /* Pointeur sur l'adresse du caractère suivant de argv[i] */
      if (i + 1 >= argc - 1) /* si aucun mot n'est indiqué après la commande */
        switchCmdLettre(&a, nomFichier, cmd[0], NULL);
      else
        switchCmdLettre(&a, nomFichier, cmd[0], (unsigned char*) argv[++i]);
    }
  }

  freeArbre(a);
}
  else{ 
    printHelp();
  }

return 0;

}
